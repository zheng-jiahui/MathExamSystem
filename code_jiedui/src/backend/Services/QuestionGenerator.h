#ifndef PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_QUESTIONGENERATOR_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_QUESTIONGENERATOR_H_

#include <random>
#include <string>
#include <vector>

using namespace std;

class QuestionGenerator {
	public:
		/**
		* @brief 生成考题
		* @return string 生成的考题字符串
		*/
		virtual string GenerateQuestion() = 0;
		virtual ~QuestionGenerator() = default;
};

class PrimaryGenerator : public QuestionGenerator {
	private:
		static mt19937 gen;
		static bool initialized;

		/**
		* @brief 初始化随机数生成器
		*/
		void InitRandom();

		/**
		* @brief 生成操作数
		* @param count 操作数数量
		* @return vector<int> 操作数向量
		*/
		vector<int> GenerateOperands(int count);

		/**
		* @brief 生成运算符
		* @param count 运算符数量
		* @return vector<char> 运算符向量
		*/
		vector<char> GenerateOperators(int count);

		/**
		* @brief 构建考题字符串
		* @param operands 操作数向量
		* @param operators 运算符向量
		* @param use_brackets 是否使用括号
		* @return string 构建的考题字符串
		*/
		string BuildQuestion(const vector<int>& operands, const vector<char>& operators,
		                     bool use_brackets);

	public:
		/**
		* @brief 生成小学级别考题
		* @return string 生成的考题字符串
		*/
		string GenerateQuestion() override;
};

class JuniorGenerator : public QuestionGenerator {
	private:
		static mt19937 gen;
		static bool initialized;

		/**
		* @brief 初始化随机数生成器
		*/
		void InitRandom();

		/**
		* @brief 生成特殊运算符
		* @return string 特殊运算符字符串
		*/
		string GenerateSpecialOperator();

		/**
		* @brief 构建考题字符串
		* @param has_special_op 是否包含特殊运算符的引用
		* @param operands_count 操作数数量
		* @return string 构建的考题字符串
		*/
		string BuildQuestion(bool& has_special_op, int operands_count);

	public:
		/**
		* @brief 生成初中级别考题
		* @return string 生成的考题字符串
		*/
		string GenerateQuestion() override;
};

class SeniorGenerator : public QuestionGenerator {
	private:
		static mt19937 gen;
		static bool initialized;

		/**
		* @brief 初始化随机数生成器
		*/
		void InitRandom();

		/**
		* @brief 生成三角函数
		* @return string 三角函数字符串
		*/
		string GenerateTrigFunction();

		/**
		* @brief 构建考题字符串
		* @param has_trig 是否包含三角函数的引用
		* @param operands_count 操作数数量
		* @return string 构建的考题字符串
		*/
		string BuildQuestion(bool& has_trig, int operands_count);

	public:
		/**
		* @brief 生成高中级别考题
		* @return string 生成的考题字符串
		*/
		string GenerateQuestion() override;
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_QUESTIONGENERATOR_H_
