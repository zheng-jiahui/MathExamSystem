#ifndef PAIR_PROJECT2_0_SRC_BACKEND_MODELS_EXAMRESULT_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_MODELS_EXAMRESULT_H_

/**
 * @brief 考试结果数据结构
 */
struct ExamResult {
	int totalQuestions;// 总题目数
	int correctAnswers;// 正确答案数
	double score;// 得分（百分比）
	std::string userType;// 用户类型

	/**
	 * @brief 默认构造函数
	 * 初始化所有成员为默认值
	 */
	ExamResult() : totalQuestions(0), correctAnswers(0), score(0.0) {}

	/**
	 * @brief 参数化构造函数
	 * @param total 总题目数
	 * @param correct 正确答案数
	 * @param type 用户类型
	 * 自动计算得分百分比
	 */
	ExamResult(int total, int correct, const std::string& type)
		: totalQuestions(total), correctAnswers(correct), userType(type) {
		score = totalQuestions > 0 ? (static_cast<double>(correctAnswers) / totalQuestions) * 100 : 0.0;
	}
};

#endif  // PERSONAL_PROJECT2_0_SRC_BACKEND_MODELS_EXAMRESULT_H_
