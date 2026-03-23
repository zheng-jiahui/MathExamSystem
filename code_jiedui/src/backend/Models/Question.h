#ifndef PAIR_PROJECT2_0_SRC_BACKEND_MODELS_QUESTION_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_MODELS_QUESTION_H_

#include <string>
#include <vector>

/**
 * @brief 题目数据结构
 */
struct Question {
	std::string content;// 题目内容（题干）
	std::vector<std::string> options;// 选项列表（通常为4个选项）
	int correctAnswer;// 正确答案索引（0-3对应A/B/C/D）
	int userAnswer;// 用户答案索引（-1表示未回答）

	/**
	 * @brief 默认构造函数
	 * 初始化正确答案为0（选项A），用户答案为-1（未回答）
	 */
	Question() : correctAnswer(0), userAnswer(-1) {}

	/**
	 * @brief 参数化构造函数
	 * @param cnt 题目内容
	 * @param opts 选项列表
	 * @param correct 正确答案索引
	 * 初始化用户答案为-1（未回答）
	 */
	Question(const std::string& cnt, const std::vector<std::string>& opts, int correct)
		: content(cnt), options(opts), correctAnswer(correct), userAnswer(-1) {}
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_MODELS_QUESTION_H_
