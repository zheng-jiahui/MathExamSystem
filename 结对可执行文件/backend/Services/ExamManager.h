#ifndef PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_EXAMMANAGER_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_EXAMMANAGER_H_

#include "../Models/Question.h"
#include "../Models/ExamResult.h"
#include "../Utils/FileHelper.h"

#include <vector>
#include <string>
#include <fstream>

class ExamManager {
	public:
		/**
		* @brief 构造函数
		* @param dataFile 考试数据文件路径
		*/
		explicit ExamManager(const std::string& dataFile);

		/**
		* @brief 开始新的考试
		* @param questions 考题列表
		* @param userType 用户类型
		* @return bool 成功开始考试返回true，否则返回false
		*/
		bool StartNewExam(const std::vector<Question>& questions, const std::string& userType);

		/**
		* @brief 获取当前考题
		* @return Question 当前考题对象
		*/
		Question GetCurrentQuestion();

		/**
		* @brief 获取当前考题索引
		* @return int 当前考题索引（从0开始）
		*/
		int GetCurrentQuestionIndex();

		/**
		* @brief 获取考题总数
		* @return int 考题总数
		*/
		int GetTotalQuestions();

		/**
		* @brief 提交当前考题答案
		* @param answer 用户选择的答案索引
		* @return bool 成功提交返回true，否则返回false
		*/
		bool SubmitAnswer(int answer);

		/**
		* @brief 移动到下一题
		* @return bool 成功移动返回true，已经是最后一题返回false
		*/
		bool MoveToNextQuestion();

		/**
		* @brief 移动到上一题
		* @return bool 成功移动返回true，已经是第一题返回false
		*/
		bool MoveToPreviousQuestion();

		/**
		* @brief 提交考试
		* @return ExamResult 考试结果对象
		*/
		ExamResult SubmitExam();

		/**
		* @brief 取消考试
		*/
		void CancelExam();

		/**
		* @brief 计算正确答案数量
		* @return int 正确答案数量
		*/
		int CalculateCorrectAnswers();

		/**
		* @brief 保存考试结果到文件
		* @param result 考试结果对象
		*/
		void SaveExamResultToFile(const ExamResult& result);

		/**
		* @brief 生成考试结果头部信息
		* @param result 考试结果对象
		* @return std::string 格式化后的头部信息字符串
		*/
		std::string GenerateExamResultHeader(const ExamResult& result);

		/**
		* @brief 生成详细答题报告
		* @return std::string 详细答题报告字符串
		*/
		std::string GenerateDetailedAnswerReport();

		/**
		* @brief 生成单题报告
		* @param index 考题索引
		* @return std::string 单题报告字符串
		*/
		std::string GenerateQuestionReport(size_t index);

		/**
		* @brief 生成选项报告
		* @param options 选项列表
		* @return std::string 选项报告字符串
		*/
		std::string GenerateOptionsReport(const std::vector<std::string>& options);

		/**
		* @brief 清除考试数据
		*/
		void ClearExamData();

		/**
		* @brief 检查考试是否进行中
		* @return bool 考试进行中返回true，否则返回false
		*/
		bool IsExamInProgress();

		/**
		* @brief 从文件加载考试数据
		* @param file 输入文件流
		*/
		void LoadExamFromFile(std::ifstream& file);

		/**
		* @brief 解析考题行
		* @param line 输入字符串行
		* @param currentQuestion 当前考题对象的引用
		*/
		void ParseQuestionLine(const std::string& line, Question& currentQuestion);

		/**
		* @brief 解析考题选项
		* @param line 输入字符串行
		* @param currentQuestion 当前考题对象的引用
		*/
		void ParseQuestionOption(const std::string& line, Question& currentQuestion);

		/**
		* @brief 解析考试信息行
		* @param line 输入字符串行
		* @param expectedTotalQuestions 预期考题总数的引用
		*/
		void ParseExamInfoLine(const std::string& line, int& expectedTotalQuestions);

		/**
		* @brief 安全字符串转整数
		* @param str 输入字符串
		* @return int 转换后的整数值，转换失败返回0
		*/
		int SafeStoi(const std::string& str);

		/**
		* @brief 验证并设置考试状态
		*/
		void ValidateAndSetExamState();

		/**
		* @brief 检查考试状态是否有效
		* @return bool 考试状态有效返回true，否则返回false
		*/
		bool IsValidExamState();

		/**
		* @brief 清除考试状态
		*/
		void ClearExamState();

		/**
		* @brief 移除损坏的文件
		*/
		void RemoveCorruptedFile();

	private:
		/**
		* @brief 保存考试数据到文件
		*/
		void SaveExamData();

		/**
		* @brief 从文件加载考试数据
		*/
		void LoadExamData();

		std::string dataFile_;
		std::vector<Question> questions_;
		int currentQuestionIndex_ = -1;
		bool examInProgress_ = false;
		std::string currentUserType_;
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_EXAMMANAGER_H_
