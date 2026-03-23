#include "QuestionService.h"
#include "../Utils/StringHelper.h"
#include <random>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <map>

using namespace std;

// 表达式计算器类 - 处理数学表达式的解析和计算
class ExpressionCalculator {
	private:
		static map<char, int> opPriority;// 运算符优先级映射

		static bool isOperator(char c) {
			return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
		}

		static double applyOperator(double a, double b, char op) {
			switch (op) {
				case '+':
					return a + b;
				case '-':
					return a - b;
				case '*':
					return a * b;
				case '/':
					if (b == 0) throw runtime_error("");
					return a / b;
				case '^':
					return pow(a, b);
				default:
					throw runtime_error("");
			}
		}

		// 将中缀表达式转换为后缀表达式（逆波兰表示法）
		static vector<string> toRPN(const string& expression) {
			vector<string> output;
			stack<char> operators;
			string number;

			ProcessExpression(expression, output, operators, number);
			ProcessRemainingOperators(output, operators);

			return output;
		}

		static void ProcessExpression(const string& expression, vector<string>& output,
		                              stack<char>& operators, string& number) {
			for (size_t i = 0; i < expression.length(); i++) {
				char c = expression[i];

				if (isspace(c)) {
					FlushNumber(output, number);// 遇到空格刷新数字
					continue;
				}

				if (isdigit(c) || c == '.') {
					number += c;// 构建数字
				} else {
					FlushNumber(output, number);
					ProcessOperatorOrBracket(c, output, operators);
				}
			}

			FlushNumber(output, number);
		}

		static void FlushNumber(vector<string>& output, string& number) {
			if (!number.empty()) {
				output.push_back(number);
				number.clear();
			}
		}

		static void ProcessOperatorOrBracket(char c, vector<string>& output,
		                                     stack<char>& operators) {
			if (c == '(') {
				operators.push(c);
			} else if (c == ')') {
				ProcessClosingBracket(output, operators);
			} else if (isOperator(c)) {
				ProcessOperator(c, output, operators);
			}
		}

		static void ProcessClosingBracket(vector<string>& output, stack<char>& operators) {
			// 弹出直到遇到左括号
			while (!operators.empty() && operators.top() != '(') {
				output.push_back(string(1, operators.top()));
				operators.pop();
			}

			if (!operators.empty() && operators.top() == '(') {
				operators.pop();
			} else {
				throw runtime_error("");
			}
		}

		static void ProcessOperator(char op, vector<string>& output, stack<char>& operators) {
			// 根据优先级弹出运算符
			while (!operators.empty() && ShouldPopOperator(operators.top(), op)) {
				output.push_back(string(1, operators.top()));
				operators.pop();// 弹出左括号
			}
			operators.push(op);
		}

		static bool ShouldPopOperator(char stackOp, char currentOp) {
			if (stackOp == '(') return false;
			return opPriority[stackOp] >= opPriority[currentOp];// 优先级比较
		}

		static void ProcessRemainingOperators(vector<string>& output, stack<char>& operators) {
			while (!operators.empty()) {
				if (operators.top() == '(') {
					throw runtime_error("");
				}
				output.push_back(string(1, operators.top()));
				operators.pop();
			}
		}

		// 计算后缀表达式
		static double evaluateRPN(const vector<string>& rpn) {
			stack<double> values;

			for (const auto& token : rpn) {
				if (token.length() == 1 && isOperator(token[0])) {
					if (values.size() < 2) throw runtime_error("");
					double b = values.top();
					values.pop();
					double a = values.top();
					values.pop();
					values.push(applyOperator(a, b, token[0]));
				} else {
					values.push(stod(token));// 将字符串转换为数字
				}
			}

			if (values.size() != 1) throw runtime_error("");
			return values.top();
		}

	public:
		static double Calculate(const string& expression) {
			try {
				string processed = PreprocessExpression(expression);// 预处理特殊符号
				auto rpn = toRPN(processed);// 转换为后缀表达式
				return evaluateRPN(rpn); // 计算后缀表达式
			} catch (const exception& e) {
				return 0.0;// 计算失败返回0
			}
		}

		// 预处理特殊数学符号
		static string PreprocessExpression(const string& expression) {
			string processed = expression;
			processed = ProcessSquareSymbols(processed);// 处理平方符号
			processed = ProcessSquareRootSymbols(processed);// 处理平方根符号
			processed = ProcessTrigFunctions(processed);// 处理三角函数
			return processed;
		}

		static string ProcessSquareSymbols(string processed) {
			size_t squarePos;
			// 查找并替换所有平方符号
			while ((squarePos = processed.find("²")) != string::npos) {
				processed = ReplaceSquareSymbol(processed, squarePos);
			}
			return processed;
		}

		static string ReplaceSquareSymbol(const string& processed, size_t squarePos) {
			// 找到平方符号前面的数字
			size_t numStart = FindNumberStart(processed, squarePos);
			if (numStart >= processed.length()) return processed;

			string numStr = processed.substr(numStart, squarePos - numStart);
			try {
				double num = stod(numStr);
				string result = processed;
				// 用平方值替换数字和平方符号
				result.replace(numStart, squarePos - numStart + 1, to_string(num * num));
				return result;
				//return processed.replace(numStart, squarePos - numStart + 1, to_string(num * num));
			} catch (...) {
				return processed;
			}
		}

		static string ProcessSquareRootSymbols(string processed) {
			size_t sqrtPos;
			// 查找并替换所有平方根符号
			while ((sqrtPos = processed.find("√")) != string::npos) {
				processed = ReplaceSquareRootSymbol(processed, sqrtPos);
			}
			return processed;
		}

		static string ReplaceSquareRootSymbol(const string& processed, size_t sqrtPos) {
			size_t numStart = sqrtPos + 3;// 跳过"√"和可能的空格
			size_t numEnd = FindNumberEnd(processed, numStart);
			if (numEnd > processed.length()) return processed;
			string numStr = processed.substr(numStart, numEnd - numStart);
			try {
				double num = stod(numStr);
				if (num >= 0) {
					string result = processed;
					// 用平方根值替换平方根符号和数字
					result.replace(sqrtPos, numEnd - sqrtPos, to_string(sqrt(num)));
					return result;
					//return processed.replace(sqrtPos, numEnd - sqrtPos, to_string(sqrt(num)));
				}
			} catch (...) {
				// 静默处理错误
			}
			return processed;
		}

		static string ProcessTrigFunctions(string processed) {
			// 定义三角函数处理列表
			vector<pair<string, double(*)(double)>> trigFunctions = {
				{"sin", sin}, {"cos", cos}, {"tan", tan}
			};

			// 处理每种三角函数
			for (const auto& [funcName, func] : trigFunctions) {
				processed = ProcessTrigFunction(processed, funcName, func);
			}
			return processed;
		}

		static string ProcessTrigFunction(string processed, const string& funcName, double(*func)(double)) {
			size_t funcPos;
			// 查找并替换所有三角函数
			while ((funcPos = processed.find(funcName)) != string::npos) {
				processed = ReplaceTrigFunction(processed, funcPos, funcName, func);
			}
			return processed;
		}

		static string ReplaceTrigFunction(const string& processed, size_t funcPos,
		                                  const string& funcName, double(*func)(double)) {
			// 找到角度值（度）
			size_t angleStart = funcPos + funcName.length();
			size_t degreePos = processed.find("°", angleStart);
			if (degreePos == string::npos) return processed;

			string angleStr = processed.substr(angleStart, degreePos - angleStart);
			try {
				double angle = stod(angleStr);
				double radians = angle * M_PI / 180.0;// 度转弧度
				double resultVal = CalculateTrigValue(func, radians, funcName);
				string result = processed;
				// 用三角函数值替换函数调用
				result.replace(funcPos, degreePos - funcPos + 1, to_string(resultVal));
				return result;
				//return processed.replace(funcPos, degreePos - funcPos + 1, to_string(result));
			} catch (...) {
				return processed;
			}
		}

		static double CalculateTrigValue(double(*func)(double), double radians, const string& funcName) {
			double result = func(radians);

			// 处理特殊角度
			if (funcName == "tan" && isinf(result)) {
				result = 1.0; // 避免无穷大
			}

			// 处理浮点数精度问题
			if (fabs(result) < 1e-10) {
				result = 0.0;
			}

			return result;
		}

		// 工具函数：查找数字的起始和结束位置
		static size_t FindNumberStart(const string& str, size_t endPos) {
			size_t start = endPos;
			while (start > 0 && (isdigit(str[start - 1]) || str[start - 1] == '.')) {
				start--;
			}
			return start;
		}

		static size_t FindNumberEnd(const string& str, size_t startPos) {
			size_t end = startPos;
			while (end < str.length() && (isdigit(str[end]) || str[end] == '.')) {
				end++;
			}
			return end;
		}
};

// 初始化运算符优先级
map<char, int> ExpressionCalculator::opPriority = {
	{'+', 1}, {'-', 1},
	{'*', 2}, {'/', 2},
	{'^', 3}
};

QuestionService::QuestionService()
	: currentUsername_("") { // 显式初始化当前用户名为空
	// userQuestionHistory_ 会自动初始化
	cout << "QuestionService 初始化完成" << endl;
}

QuestionService::~QuestionService() {
	cout << "QuestionService 清理完成" << endl;
}

vector<Question> QuestionService::GenerateQuestions(const std::string& userType, int count) {
	auto generator = CreateGenerator(userType);
	if (!generator) {
		return {};// 创建生成器失败返回空向量
	}

	return GenerateValidQuestions(generator, userType, count);
}

vector<Question> QuestionService::GenerateValidQuestions(unique_ptr<QuestionGenerator>& generator,
        const std::string& userType, int count) {
	vector<Question> questions;
	int attempts = 0;
    const int maxAttempts = count * 40000;// 最大尝试次数，避免无限循环

	// 持续生成直到达到目标数量或超过最大尝试次数
	while (questions.size() < count && attempts < maxAttempts) {
		Question question = GenerateSingleQuestion(generator, userType);
		if (IsValidQuestion(question)) {
			questions.push_back(question);
			AddToQuestionHistory(question.content);// 记录题目历史
		}
		attempts++;
	}

	ReportGenerationResult(questions.size(), count);
	return questions;
}

Question QuestionService::GenerateSingleQuestion(unique_ptr<QuestionGenerator>& generator,
        const std::string& userType) {
	string questionText = generator->GenerateQuestion();
	string expression = ExtractExpression(questionText);
	// 检查题目是否重复
	if (IsDuplicateQuestion(expression)) {
		return Question(); // 返回空题目表示重复
	}

	// 计算正确答案
	double correctValue = ExpressionCalculator::Calculate(expression);
	if (!IsValidAnswer(correctValue)) {
		return Question(); // 返回空题目表示答案无效
	}

	return BuildQuestionObject(questionText, correctValue, userType);
}

string QuestionService::ExtractExpression(const string& questionText) {
	string expression = questionText;
	// 移除末尾的" = "
	if (StringHelper::EndsWith(expression, " = ")) {
		expression = expression.substr(0, expression.length() - 3);
	}
	return expression;
}

bool QuestionService::IsDuplicateQuestion(const string& expression) {
	// 检查当前用户的题目历史中是否已存在该表达式
	return userQuestionHistory_[currentUsername_].count(expression) > 0;
}

bool QuestionService::IsValidAnswer(double correctValue) {
	// 验证答案是否有效：有限、非负、不超过10000
	return isfinite(correctValue) && correctValue >= 0 && correctValue <= 10000;
}

Question QuestionService::BuildQuestionObject(const string& questionText, double correctValue,
        const std::string& userType) {
	// 生成包含正确答案的选项
	auto optionsResult = GenerateOptionsWithCorrectIndex(correctValue, userType);

	// 检查选项是否唯一
	if (!HasUniqueOptions(optionsResult.options)) {
		return Question(); // 返回空题目表示选项不唯一
	}

	Question question;
	question.content = questionText;
	question.options = optionsResult.options;
	question.correctAnswer = optionsResult.correctIndex;
	question.userAnswer = -1;// 初始化为未回答

	return question;
}

bool QuestionService::IsValidQuestion(const Question& question) {
	// 检查题目内容和非空选项
	return !question.content.empty() && !question.options.empty();
}

bool QuestionService::HasUniqueOptions(const vector<string>& options) {
	set<string> uniqueOptions;
	// 使用set检查选项唯一性
	for (const auto& option : options) {
		if (!uniqueOptions.insert(option).second) {
			return false;// 插入失败说明有重复
		}
	}
	return true;
}

void QuestionService::AddToQuestionHistory(const string& questionContent) {
	string expression = ExtractExpression(questionContent);
	userQuestionHistory_[currentUsername_].insert(expression);// 添加到用户题目历史
}

void QuestionService::ReportGenerationResult(int generatedCount, int targetCount) {
	// 报告生成结果
	if (generatedCount < targetCount) {
		cout << "⚠️  生成了 " << generatedCount << " 道有效题目（目标 " << targetCount << " 道）" << endl;
	} else {
		cout << "✅ 成功生成 " << generatedCount << " 道题目" << endl;
	}
}

OptionsResult QuestionService::GenerateOptionsWithCorrectIndex(double correctValue, const std::string& userType) {
	OptionsResult result;
	string correctAnswer = FormatAnswer(correctValue);
	result.options.push_back(correctAnswer);// 添加正确答案

	// 生成错误答案
	vector<string> wrongAnswers = GenerateWrongAnswers(correctValue, userType);
	result.options.insert(result.options.end(), wrongAnswers.begin(), wrongAnswers.end());

	// 打乱选项并记录正确答案位置
	ShuffleOptionsAndFindCorrect(result, correctAnswer);
	return result;
}

vector<string> QuestionService::GenerateWrongAnswers(double correctValue, const std::string& userType) {
	vector<string> wrongAnswers;
	random_device rd;
	mt19937 gen(rd());

	// 生成最多3个错误答案
	for (int i = 0; i < 3 && wrongAnswers.size() < 3; i++) {
		double wrongValue = CalculateWrongAnswer(correctValue, userType, i, gen);
		string wrongAnswer = FormatAnswer(wrongValue);

		// 验证错误答案有效性
		if (IsValidWrongAnswer(wrongAnswer, correctValue, wrongAnswers)) {
			wrongAnswers.push_back(wrongAnswer);
		}
	}

	// 确保有3个错误答案
	return EnsureThreeWrongAnswers(wrongAnswers, correctValue);
}

double QuestionService::CalculateWrongAnswer(double correctValue, const std::string& userType, int index, mt19937& gen) {
	// 根据用户类型调用不同的错误答案生成策略
	if (userType == "小学") {
		return CalculatePrimaryWrongAnswer(correctValue, index, gen);
	} else if (userType == "初中") {
		return CalculateJuniorWrongAnswer(correctValue, index, gen);
	} else {
		return CalculateSeniorWrongAnswer(correctValue, index, gen);
	}
}

double QuestionService::CalculatePrimaryWrongAnswer(double correctValue, int index, mt19937& gen) {
	// 小学：简单的加减偏移
	uniform_int_distribution<> intDis(1, 10);
	int offset = intDis(gen) * (index % 2 == 0 ? 1 : -1);
	return correctValue + offset;
}

double QuestionService::CalculateJuniorWrongAnswer(double correctValue, int index, mt19937& gen) {
	// 初中：百分比偏移
	uniform_real_distribution<> percentDis(0.1, 0.3);
	double percent = percentDis(gen);
	return index % 2 == 0 ? correctValue * (1.0 + percent) : correctValue * (1.0 - percent);
}

double QuestionService::CalculateSeniorWrongAnswer(double correctValue, int index, mt19937& gen) {
	// 高中：多种错误模式
	uniform_real_distribution<> valueDis(0.5, 2.0);
	if (index % 3 == 0) return correctValue + valueDis(gen);// 加法错误
	if (index % 3 == 1) return correctValue - valueDis(gen);// 减法错误
	return correctValue * valueDis(gen);// 乘法错误
}

bool QuestionService::IsValidWrongAnswer(const string& wrongAnswer, double correctValue, const vector<string>& existingWrongs) {
	// 检查错误答案是否与正确答案相同
	if (wrongAnswer == FormatAnswer(correctValue)) return false;

	// 检查是否与已有错误答案重复
	for (const auto& existing : existingWrongs) {
		if (wrongAnswer == existing) return false;
	}

	return true;
}

vector<string> QuestionService::EnsureThreeWrongAnswers(vector<string> wrongAnswers, double correctValue) {
	// 如果错误答案不足3个，补充默认错误答案
	while (wrongAnswers.size() < 3) {
		double backupValue = correctValue + wrongAnswers.size() + 1;
		wrongAnswers.push_back(FormatAnswer(backupValue));
	}
	return wrongAnswers;
}

void QuestionService::ShuffleOptionsAndFindCorrect(OptionsResult& result, const string& correctAnswer) {
	random_device rd;
	mt19937 gen(rd());
	// 打乱选项顺序
	shuffle(result.options.begin(), result.options.end(), gen);

	// 找到正确答案的新位置
	for (size_t i = 0; i < result.options.size(); i++) {
		if (result.options[i] == correctAnswer) {
			result.correctIndex = i;
			break;
		}
	}
}

string QuestionService::FormatAnswer(double value) {
	// 处理无效值
	if (!isfinite(value)) {
		return "0"; // 返回默认值
	}

	// 处理非常小的值
	if (fabs(value) < 1e-10) {
		return "0";
	}

	// 如果是整数，显示为整数；否则显示2位小数
	if (fabs(value - round(value)) < 1e-6) {
		return to_string(static_cast<int>(round(value)));
	} else {
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "%.2f", value);
		string result = buffer;
		// 移除多余的0
		if (result.find('.') != string::npos) {
			while (result.back() == '0') result.pop_back();
			if (result.back() == '.') result.pop_back();
		}
		return result;
	}
}

unique_ptr<QuestionGenerator> QuestionService::CreateGenerator(const std::string& userType) {
	// 根据用户类型创建对应的题目生成器
	if (userType == "小学") {
		return make_unique<PrimaryGenerator>();
	} else if (userType == "初中") {
		return make_unique<JuniorGenerator>();
	} else if (userType == "高中") {
		return make_unique<SeniorGenerator>();
	}
	return nullptr;
}

bool QuestionService::IsDuplicate(const std::string& question) {
	if (currentUsername_.empty()) {
		return false;
	}
	return userQuestionHistory_[currentUsername_].count(question) > 0;
}

void QuestionService::ClearUserHistory(const std::string& username) {
	userQuestionHistory_.erase(username);// 清除用户题目历史
	if (currentUsername_ == username) {
		currentUsername_.clear();// 如果是当前用户，清空当前用户名
	}
	cout << "已清除用户 " << username << " 的题目历史" << endl;
}

void QuestionService::SetCurrentUser(const std::string& username) {
	currentUsername_ = username;

	// 如果该用户还没有题目历史记录，初始化一个空集合
	if (userQuestionHistory_.find(username) == userQuestionHistory_.end()) {
		userQuestionHistory_[username] = std::set<std::string>();
	}

	cout << "题目服务已切换到用户: " << username << endl;
}
