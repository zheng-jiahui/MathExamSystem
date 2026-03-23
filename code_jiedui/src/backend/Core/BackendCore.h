#ifndef PAIR_PROJECT2_0_SRC_BACKEND_CORE_BACKENDCORE_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_CORE_BACKENDCORE_H_

#include "../Models/UserInfo.h"
#include "../Models/Question.h"
#include "../Models/ExamResult.h"
#include "../Services/UserManager.h"
#include "../Services/ExamManager.h"
#include "../Services/QuestionService.h"
#include <string>
#include <vector>
#include <memory>

class BackendCore {
	public:
		/**
		* @brief 获取单例实例
		* @return BackendCore& 单例实例的引用
		*/
		static BackendCore& GetInstance();

		// 禁用拷贝和赋值
		BackendCore(const BackendCore&) = delete;
		BackendCore& operator=(const BackendCore&) = delete;

		// ==================== 用户管理API ====================

		/**
		 * @brief 注册用户（第一步：发送验证码）
                 * @param username 用户名
		 * @param email 邮箱地址
		 * @param outRegistrationCode 输出注册码的引用
		 * @return bool 注册成功返回true，否则返回false
		 */
                bool RegisterUser(const std::string& username,const std::string& email, std::string& outRegistrationCode);

		/**
		* @brief 完成注册（第二步：验证信息并创建账户）
                * @param username 用户名
		* @param email 邮箱地址
		* @param regCode 注册码
		* @param password 密码
		* @param confirmPassword 确认密码
		* @param userType 用户类型（"小学"/"初中"/"高中"）
		* @return bool 注册完成返回true，否则返回false
		*/
                bool CompleteRegistrationWithType(const std::string& username,const std::string& email, const std::string& regCode,
		                                  const std::string& password, const std::string& confirmPassword,
		                                  const std::string& userType);

		/**
		* @brief 用户登录
		* @param username 用户名
		* @param password 密码
		* @return bool 登录成功返回true，否则返回false
		*/
		bool Login(const std::string& username, const std::string& password);

		/**
		* @brief 修改密码
		* @param oldPassword 旧密码
		* @param newPassword 新密码
		* @param confirmNewPassword 确认新密码
		* @return bool 修改成功返回true，否则返回false
		*/
		bool ChangePassword(const std::string& oldPassword, const std::string& newPassword,
		                    const std::string& confirmNewPassword);

		/**
		* @brief 用户登出
		*/
		void Logout();

		// ==================== 题目生成API ====================

		/**
		 * @brief 生成考试题目
		 * @param userType 用户类型
		 * @param questionCount 题目数量
		 * @return bool 生成成功返回true，否则返回false
		 */
		bool GenerateExam(const std::string& userType, int questionCount);

		/**
		* @brief 获取当前题目
		* @return Question 当前题目对象
		*/
		Question GetCurrentQuestion();

		/**
		* @brief 获取当前题目索引
		* @return int 当前题目索引（从0开始）
		*/
		int GetCurrentQuestionIndex();

		/**
		* @brief 获取题目总数
		* @return int 题目总数
		*/
		int GetTotalQuestions();

		/**
		* @brief 提交当前题目答案
		* @param answer 用户选择的答案索引（0-3对应A/B/C/D）
		* @return bool 提交成功返回true，否则返回false
		*/
		bool SubmitAnswer(int answer);

		/**
		* @brief 移动到下一题
		* @return bool 成功移动返回true，已经是最后一题返回false
		*/
		bool MoveToNextQuestion();

		/**
		* @brief 切换用户类型
		* @param newUserType 新的用户类型
		* @return bool 切换成功返回true，否则返回false
		*/
		bool MoveToPreviousQuestion();

		/**
		 * @brief 切换用户类型
		 * @param newUserType 新的用户类型
		 * @return bool 切换成功返回true，否则返回false
		 */
		bool SwitchUserType(const std::string& newUserType);

		// ==================== 考试管理API ====================

		/**
		 * @brief 提交考试
		 * @return ExamResult 考试结果对象
		 */
		ExamResult SubmitExam();

		/**
		* @brief 取消考试
		*/
		void CancelExam();

		// ==================== 用户状态API ====================

		/**
		 * @brief 检查用户是否已登录
		 * @return bool 已登录返回true，否则返回false
		 */
		bool IsLoggedIn();

		/**
		* @brief 获取当前用户信息
		* @return UserInfo 当前用户信息对象
		*/
		UserInfo GetCurrentUser();

		/**
		* @brief 获取当前用户类型
		* @return std::string 用户类型字符串
		*/
		std::string GetCurrentUserType();

		/**
		* @brief 设置当前用户类型
		* @param userType 用户类型
		*/
		void SetCurrentUserType(const std::string& userType);

		// ==================== 工具函数 ====================

		/**
		 * @brief 验证密码复杂度
		 * @param password 密码字符串
		 * @return bool 符合复杂度要求返回true，否则返回false
		 */
		bool ValidatePassword(const std::string& password);

		/**
		* @brief 验证邮箱格式
		* @param email 邮箱地址
		* @return bool 格式正确返回true，否则返回false
		*/
		bool IsValidEmail(const std::string& email);

	private:
		/**
		* @brief 私有构造函数（单例模式）
		*/
		BackendCore();

		/**
		* @brief 析构函数
		*/
		~BackendCore();

		UserManager userManager_;// 用户管理服务
		ExamManager examManager_;// 考试管理服务
		QuestionService questionService_;// 题目生成服务

		UserInfo currentUser_;// 当前用户信息
		bool isLoggedIn_ = false;// 登录状态标志
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_CORE_BACKENDCORE_H_
