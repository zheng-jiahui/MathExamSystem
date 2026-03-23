#ifndef PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_QUESTIONSERVICE_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_QUESTIONSERVICE_H_

#include "../Models/Question.h"
#include "QuestionGenerator.h"
#include <vector>
#include <memory>
#include <string>
#include <set>
#include <map>

struct OptionsResult {
	std::vector<std::string> options;
	int correctIndex;
};

class QuestionService {
	public:
		/**
		* @brief 构造函数
		*/
		QuestionService();
		/**
		* @brief 析构函数
		*/
		~QuestionService();


		/**
		* @brief 生成考题列表
		* @param userType 用户类型
		* @param count 考题数量
		* @return vector<Question> 考题对象向量
		*/
		std::vector<Question> GenerateQuestions(const std::string& userType, int count);

		/**
		* @brief 清除用户历史记录
		* @param username 用户名
		*/
		void ClearUserHistory(const std::string& username);

		/**
		* @brief 设置当前用户
		* @param username 用户名
		*/
		void SetCurrentUser(const std::string& username);

		/**
		* @brief 生成错误答案
		* @param correctValue 正确答案值
		* @param userType 用户类型
		* @return vector<string> 错误答案字符串向量
		*/
		vector<string> GenerateWrongAnswers(double correctValue, const std::string& userType);

		/**
		* @brief 计算错误答案值
		* @param correctValue 正确答案值
		* @param userType 用户类型
		* @param index 错误答案索引
		* @param gen 随机数生成器
		* @return double 计算出的错误答案值
		*/
		double CalculateWrongAnswer(double correctValue, const std::string& userType, int index, mt19937& gen);

		/**
		* @brief 计算小学级别错误答案
		* @param correctValue 正确答案值
		* @param index 错误答案索引
		* @param gen 随机数生成器
		* @return double 计算出的错误答案值
		*/
		double CalculatePrimaryWrongAnswer(double correctValue, int index, mt19937& gen);

		/**
		* @brief 计算初中级别错误答案
		* @param correctValue 正确答案值
		* @param index 错误答案索引
		* @param gen 随机数生成器
		* @return double 计算出的错误答案值
		*/
		double CalculateJuniorWrongAnswer(double correctValue, int index, mt19937& gen);

		/**
		* @brief 计算高中级别错误答案
		* @param correctValue 正确答案值
		* @param index 错误答案索引
		* @param gen 随机数生成器
		* @return double 计算出的错误答案值
		*/
		double CalculateSeniorWrongAnswer(double correctValue, int index, mt19937& gen);

		/**
		* @brief 验证错误答案是否有效
		* @param wrongAnswer 错误答案字符串
		* @param correctValue 正确答案值
		* @param existingWrongs 已存在的错误答案向量
		* @return bool 有效返回true，否则返回false
		*/
		bool IsValidWrongAnswer(const string& wrongAnswer, double correctValue, const vector<string>& existingWrongs);

		/**
		* @brief 确保有三个错误答案
		* @param wrongAnswers 错误答案向量
		* @param correctValue 正确答案值
		* @return vector<string> 包含三个错误答案的向量
		*/
		vector<string> EnsureThreeWrongAnswers(vector<string> wrongAnswers, double correctValue);

		/**
		* @brief 打乱选项并找到正确答案索引
		* @param result 选项结果结构体的引用
		* @param correctAnswer 正确答案字符串
		*/
		void ShuffleOptionsAndFindCorrect(OptionsResult& result, const string& correctAnswer);

		/**
		* @brief 生成有效考题列表
		* @param generator 考题生成器智能指针
		* @param userType 用户类型
		* @param count 考题数量
		* @return vector<Question> 有效考题对象向量
		*/
		vector<Question> GenerateValidQuestions(unique_ptr<QuestionGenerator>& generator,
		                                        const std::string& userType, int count);

		/**
		* @brief 生成单个考题
		* @param generator 考题生成器智能指针
		* @param userType 用户类型
		* @return Question 考题对象
		*/
		Question GenerateSingleQuestion(unique_ptr<QuestionGenerator>& generator,
		                                const std::string& userType);

		/**
		* @brief 从考题文本中提取表达式
		* @param questionText 考题文本
		* @return string 提取的表达式字符串
		*/
		string ExtractExpression(const string& questionText);

		/**
		* @brief 检查是否重复考题
		* @param expression 考题表达式
		* @return bool 重复返回true，否则返回false
		*/
		bool IsDuplicateQuestion(const string& expression);

		/**
		* @brief 验证答案是否有效
		* @param correctValue 答案值
		* @return bool 有效返回true，否则返回false
		*/
		bool IsValidAnswer(double correctValue);

		/**
		* @brief 构建考题对象
		* @param questionText 考题文本
		* @param correctValue 正确答案值
		* @param userType 用户类型
		* @return Question 构建的考题对象
		*/
		Question BuildQuestionObject(const string& questionText, double correctValue,
		                             const std::string& userType);

		/**
		* @brief 验证考题是否有效
		* @param question 考题对象
		* @return bool 有效返回true，否则返回false
		*/
		bool IsValidQuestion(const Question& question);

		/**
		* @brief 检查选项是否唯一
		* @param options 选项向量
		* @return bool 唯一返回true，否则返回false
		*/
		bool HasUniqueOptions(const vector<string>& options);

		/**
		* @brief 添加考题到历史记录
		* @param questionContent 考题内容
		*/
		void AddToQuestionHistory(const string& questionContent);

		/**
		* @brief 报告生成结果
		* @param generatedCount 已生成数量
		* @param targetCount 目标数量
		*/
		void ReportGenerationResult(int generatedCount, int targetCount);

	private:
		/**
		* @brief 创建考题生成器
		* @param userType 用户类型
		* @return unique_ptr<QuestionGenerator> 考题生成器智能指针
		*/
		std::unique_ptr<QuestionGenerator> CreateGenerator(const std::string& userType);

		/**
		* @brief 生成包含正确答案索引的选项
		* @param correctValue 正确答案值
		* @param userType 用户类型
		* @return OptionsResult 选项结果结构体
		*/
		OptionsResult GenerateOptionsWithCorrectIndex(double correctValue, const std::string& userType);

		/**
		* @brief 格式化答案
		* @param value 答案值
		* @return string 格式化后的答案字符串
		*/
		std::string FormatAnswer(double value);

		/**
		* @brief 检查是否重复考题
		* @param question 考题字符串
		* @return bool 重复返回true，否则返回false
		*/
		bool IsDuplicate(const std::string& question);

		std::map<std::string, std::set<std::string>> userQuestionHistory_;
		std::string currentUsername_;
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_QUESTIONSERVICE_H_
