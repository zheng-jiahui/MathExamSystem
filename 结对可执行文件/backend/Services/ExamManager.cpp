#include "ExamManager.h"
#include "../Utils/StringHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ExamManager::ExamManager(const std::string& dataFile) : dataFile_(dataFile) {
	LoadExamData();// 构造函数中加载考试数据
}

bool ExamManager::StartNewExam(const std::vector<Question>& questions, const std::string& userType) {
	if (questions.empty()) {
		return false;// 题目列表不能为空
	}

	questions_ = questions;
	currentQuestionIndex_ = 0;// 从第一题开始
	examInProgress_ = true;
	currentUserType_ = userType;

	SaveExamData();// 立即保存考试状态
	return true;
}

Question ExamManager::GetCurrentQuestion() {
	// 检查考试状态和索引有效性
	if (!examInProgress_ || currentQuestionIndex_ < 0 ||
	        currentQuestionIndex_ >= questions_.size()) {
		return Question();// 返回空题目对象
	}
	return questions_[currentQuestionIndex_];
}

int ExamManager::GetCurrentQuestionIndex() {
	return currentQuestionIndex_;
}

int ExamManager::GetTotalQuestions() {
	return questions_.size();
}

bool ExamManager::SubmitAnswer(int answer) {
	if (!examInProgress_ || currentQuestionIndex_ < 0 ||
	        currentQuestionIndex_ >= questions_.size()) {
		return false;// 考试未进行或索引无效
	}

	if (answer < 0 || answer >= 4) {
		return false;// 答案索引必须在0-3范围内
	}

	questions_[currentQuestionIndex_].userAnswer = answer;
	SaveExamData();// 保存答案
	return true;
}

bool ExamManager::MoveToNextQuestion() {
	if (!examInProgress_ || currentQuestionIndex_ >= questions_.size() - 1) {
		return false;// 已经是最后一题
	}

	currentQuestionIndex_++;
	SaveExamData();// 保存进度
	return true;
}

bool ExamManager::MoveToPreviousQuestion() {
	if (!examInProgress_ || currentQuestionIndex_ <= 0) {
		return false;// 已经是第一题
	}

	currentQuestionIndex_--;
	SaveExamData();// 保存进度
	return true;
}

ExamResult ExamManager::SubmitExam() {
	if (!examInProgress_) {
		return ExamResult();// 返回空的考试结果
	}

	int correctCount = CalculateCorrectAnswers();
	ExamResult result(questions_.size(), correctCount, currentUserType_);

	SaveExamResultToFile(result);// 保存考试结果到文件
	ClearExamData();// 清理考试数据

	return result;
}

int ExamManager::CalculateCorrectAnswers() {
	int correctCount = 0;
	// 遍历所有题目，统计正确答案数量
	for (const auto& question : questions_) {
		if (question.userAnswer == question.correctAnswer) {
			correctCount++;
		}
	}
	return correctCount;
}

void ExamManager::SaveExamResultToFile(const ExamResult& result) {
	// 生成带时间戳的结果文件名
	string resultFile = "exam_results/" + FileHelper::GenerateTimestampFilename(
	                        currentUserType_ + "_exam", ".txt");

	FileHelper::CreateDirectoryW("exam_results");// 确保目录存在

	stringstream ss;
	ss << GenerateExamResultHeader(result);
	ss << GenerateDetailedAnswerReport();

	FileHelper::WriteFile(resultFile, ss.str());// 写入文件
	cout << "考试结果已保存到: " << resultFile << endl;
}

string ExamManager::GenerateExamResultHeader(const ExamResult& result) {
	stringstream ss;
	ss << "=== 考试结果 ===\n";
	ss << "考试类型: " << currentUserType_ << "\n";
	ss << "总题数: " << result.totalQuestions << "\n";
	ss << "正确题数: " << result.correctAnswers << "\n";
	ss << "得分: " << result.score << "\n\n";
	return ss.str();
}

string ExamManager::GenerateDetailedAnswerReport() {
	stringstream ss;
	ss << "=== 详细答题情况 ===\n";
	// 为每道题生成详细报告
	for (size_t i = 0; i < questions_.size(); i++) {
		ss << GenerateQuestionReport(i);
	}
	return ss.str();
}

string ExamManager::GenerateQuestionReport(size_t index) {
	const auto& q = questions_[index];
	stringstream ss;

	ss << "第 " << (index + 1) << " 题:\n";
	ss << "题目: " << q.content << "\n";
	ss << GenerateOptionsReport(q.options);
	ss << "正确答案: " << char('A' + q.correctAnswer) << "\n";
	ss << "你的答案: " << (q.userAnswer >= 0 ? std::string(1, 'A' + q.userAnswer) : "未作答") << "\n";
	ss << "结果: " << (q.userAnswer == q.correctAnswer ? "正确" : "错误") << "\n\n";

	return ss.str();
}

string ExamManager::GenerateOptionsReport(const vector<string>& options) {
	stringstream ss;
	ss << "选项: \n";
	// 格式化显示所有选项
	for (size_t j = 0; j < options.size(); j++) {
		ss << "  " << char('A' + j) << ". " << options[j] << "\n";
	}
	return ss.str();
}

void ExamManager::ClearExamData() {
	examInProgress_ = false;
	questions_.clear();
	currentQuestionIndex_ = -1;
}

void ExamManager::CancelExam() {
	examInProgress_ = false;
	questions_.clear();
	currentQuestionIndex_ = -1;

	// 删除临时考试数据文件
	if (FileHelper::FileExists(dataFile_)) {
		remove(dataFile_.c_str());
	}
}

bool ExamManager::IsExamInProgress() {
	return examInProgress_;
}

void ExamManager::SaveExamData() {
	if (!examInProgress_) {
		return;// 考试未进行时不保存
	}

	ofstream file(dataFile_);
	if (!file.is_open()) {
		cerr << "无法保存考试数据到文件: " << dataFile_ << endl;
		return;
	}

	// 保存考试基本信息
	file << "USER_TYPE:" << currentUserType_ << "\n";
	file << "CURRENT_INDEX:" << currentQuestionIndex_ << "\n";
	file << "TOTAL_QUESTIONS:" << questions_.size() << "\n";

	// 保存每个题目
	for (size_t i = 0; i < questions_.size(); i++) {
		const auto& q = questions_[i];
		file << "QUESTION_START\n";
		file << "CONTENT:" << q.content << "\n";
		file << "CORRECT_ANSWER:" << q.correctAnswer << "\n";
		file << "USER_ANSWER:" << q.userAnswer << "\n";

		// 保存选项
		file << "OPTIONS_COUNT:" << q.options.size() << "\n";
		for (size_t j = 0; j < q.options.size(); j++) {
			file << "OPTION_" << j << ":" << q.options[j] << "\n";
		}
		file << "QUESTION_END\n";
	}

	file << "EXAM_END\n";
	file.close();
}

void ExamManager::LoadExamData() {
	if (!FileHelper::FileExists(dataFile_)) {
		return;// 文件不存在
	}

	ifstream file(dataFile_);
	if (!file.is_open()) {
		return;
	}

	LoadExamFromFile(file);
	file.close();

	ValidateAndSetExamState();// 验证加载的数据
}

void ExamManager::LoadExamFromFile(ifstream& file) {
	string line;
	Question currentQuestion;
	bool readingQuestion = false;
	int expectedTotalQuestions = 0;

	// 逐行读取文件内容
	while (getline(file, line)) {
		line = StringHelper::Trim(line);
		if (line.empty()) continue;

		if (line == "QUESTION_START") {
			readingQuestion = true;
			currentQuestion = Question();// 开始新题目
			continue;
		}

		if (line == "QUESTION_END") {
			if (readingQuestion) {
				questions_.push_back(currentQuestion);// 结束当前题目
				readingQuestion = false;
			}
			continue;
		}

		if (line == "EXAM_END") {
			break;// 考试数据结束
		}

		if (readingQuestion) {
			ParseQuestionLine(line, currentQuestion);// 解析题目内容
		} else {
			ParseExamInfoLine(line, expectedTotalQuestions);// 解析考试信息
		}
	}
}

void ExamManager::ParseQuestionLine(const string& line, Question& currentQuestion) {
	// 根据前缀解析不同的题目字段
	if (StringHelper::StartsWith(line, "CONTENT:")) {
		currentQuestion.content = line.substr(8);
	} else if (StringHelper::StartsWith(line, "CORRECT_ANSWER:")) {
		currentQuestion.correctAnswer = SafeStoi(line.substr(15));
	} else if (StringHelper::StartsWith(line, "USER_ANSWER:")) {
		currentQuestion.userAnswer = SafeStoi(line.substr(12));
	} else if (StringHelper::StartsWith(line, "OPTIONS_COUNT:")) {
		int optionsCount = SafeStoi(line.substr(14));
		currentQuestion.options.resize(optionsCount);// 预分配选项空间
	} else if (StringHelper::StartsWith(line, "OPTION_")) {
		ParseQuestionOption(line, currentQuestion);// 解析具体选项
	}
}

void ExamManager::ParseQuestionOption(const string& line, Question& currentQuestion) {
	size_t colonPos = line.find(':');
	if (colonPos == string::npos) return;

	// 提取选项索引
	string optionIndexStr = line.substr(7, colonPos - 7);
	int optionIndex = SafeStoi(optionIndexStr);

	// 设置选项内容
	if (optionIndex >= 0 && optionIndex < currentQuestion.options.size()) {
		currentQuestion.options[optionIndex] = line.substr(colonPos + 1);
	}
}

void ExamManager::ParseExamInfoLine(const string& line, int& expectedTotalQuestions) {
	// 解析考试基本信息
	if (StringHelper::StartsWith(line, "USER_TYPE:")) {
		currentUserType_ = line.substr(10);
	} else if (StringHelper::StartsWith(line, "CURRENT_INDEX:")) {
		currentQuestionIndex_ = SafeStoi(line.substr(14));
	} else if (StringHelper::StartsWith(line, "TOTAL_QUESTIONS:")) {
		expectedTotalQuestions = SafeStoi(line.substr(16));
	}
}

int ExamManager::SafeStoi(const string& str) {
	try {
		return stoi(str);// 安全的字符串转整数
	} catch (...) {
		return 0;// 转换失败返回0
	}
}

void ExamManager::ValidateAndSetExamState() {
	if (questions_.empty()) {
		ClearExamState();// 没有题目则清除状态
		return;
	}

	if (IsValidExamState()) {
		examInProgress_ = true;// 状态有效则恢复考试
	} else {
		ClearExamState();
		RemoveCorruptedFile();// 状态无效则清除损坏文件
	}
}

bool ExamManager::IsValidExamState() {
	// 检查当前索引是否在有效范围内
	return currentQuestionIndex_ >= 0 &&
	       currentQuestionIndex_ < questions_.size();
}

void ExamManager::ClearExamState() {
	questions_.clear();
	currentQuestionIndex_ = -1;
	examInProgress_ = false;
}

void ExamManager::RemoveCorruptedFile() {
	// 删除损坏的数据文件
	if (FileHelper::FileExists(dataFile_)) {
		remove(dataFile_.c_str());
	}
}
