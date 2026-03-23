#include "BackendCore.h"
#include <iostream>

using namespace std;

BackendCore::BackendCore()
	: userManager_("users.dat"),// 初始化用户管理器，指定用户数据文件
	  examManager_("exam_data.dat"),// 初始化考试管理器，指定考试数据文件
	  questionService_() {// 初始化题目服务
	cout << "BackendCore 初始化完成" << endl;
}

BackendCore::~BackendCore() {
	cout << "BackendCore 清理完成" << endl;
}

BackendCore& BackendCore::GetInstance() {
	static BackendCore instance;// 静态局部变量，保证线程安全的单例
	return instance;
}

bool BackendCore::CompleteRegistrationWithType(const std::string& username,const std::string& email, const std::string& regCode,
        const std::string& password, const std::string& confirmPassword,
        const std::string& userType) {
	cout << "正在验证注册信息..." << endl;
// 委托给UserManager完成注册流程
        return userManager_.CompleteRegistrationWithType(username,email, regCode, password, confirmPassword, userType);
}

bool BackendCore::RegisterUser(const std::string& username, const std::string& email, std::string& outRegistrationCode) {
    cout << "正在验证用户名和邮箱..." << endl;

    // 先验证用户名格式
    if (username.empty()) {
        cerr << "❌ 用户名不能为空" << endl;
        return false;
    }

    // 验证邮箱格式
    if (!IsValidEmail(email)) {
        cerr << "❌ 邮箱格式验证失败" << endl;
        return false;
    }

    // 委托给UserManager处理注册请求
    return userManager_.RegisterUser(username, email, outRegistrationCode);
}

bool BackendCore::SwitchUserType(const std::string& newUserType) {
	if (!isLoggedIn_) {
		cerr << "❌ 请先登录" << endl;
		return false;
	}

	// 验证用户类型
	if (newUserType != "小学" && newUserType != "初中" && newUserType != "高中") {
		cerr << "❌ 用户类型必须是小学、初中或高中" << endl;
		return false;
	}

	// 如果切换的类型与当前类型相同，直接返回成功
	if (currentUser_.userType == newUserType) {
		cout << "✅ 当前已经是" << newUserType << "类型，无需切换" << endl;
		return true;
	}

	// 更新当前用户类型
	string oldType = currentUser_.userType;
	currentUser_.userType = newUserType;

	// 更新持久化存储
	if (userManager_.UpdateUserType(currentUser_.username, newUserType)) {
		cout << "✅ 用户类型已从 " << oldType << " 切换为 " << newUserType << endl;
		cout << " 现在可以生成" << newUserType << "数学题目" << endl;
		return true;
	} else {
		// 如果更新失败，恢复原来的类型
		currentUser_.userType = oldType;
		cerr << "❌ 切换用户类型失败" << endl;
		return false;
	}
}

bool BackendCore::Login(const std::string& username, const std::string& password) {
	// 输入验证
	if (username.empty()) {
		cerr << "❌ 请输入用户名" << endl;
		return false;
	}

	if (password.empty()) {
		cerr << "❌ 请输入密码" << endl;
		return false;
	}

	cout << "正在验证用户信息..." << endl;

	UserInfo user;
// 调用UserManager进行身份认证
	if (userManager_.Authenticate(username, password, user)) {
		currentUser_ = user;
		isLoggedIn_ = true;

		// 设置题目服务的当前用户
		questionService_.SetCurrentUser(username);

		cout << "  登录成功！" << endl;
		cout << "   用户名: " << user.username << endl;
		cout << "   用户类型: " << user.userType << endl;
		cout << "   邮箱: " << user.email << endl;

		return true;
	}

	// 认证失败已经在UserManager中输出了详细错误信息
	return false;
}

bool BackendCore::ChangePassword(const std::string& oldPassword, const std::string& newPassword,
                                 const std::string& confirmNewPassword) {
	if (!isLoggedIn_) {
        cerr << "请先登录" << endl;
		return false;
	}

	// 检查输入是否为空
	if (oldPassword.empty()) {
        cerr << " 请输入原密码" << endl;
		return false;
	}

	if (newPassword.empty()) {
        cerr << " 请输入新密码" << endl;
		return false;
	}

	if (confirmNewPassword.empty()) {
        cerr << " 请确认新密码" << endl;
		return false;
	}

	cout << "正在验证密码信息..." << endl;
    // 委托给UserManager处理密码修改
	bool result = userManager_.ChangePassword(currentUser_.username, oldPassword, newPassword, confirmNewPassword);

	if (result) {
		cout << "密码已更新，下次登录请使用新密码" << endl;
    } else {
        cout << "密码修改失败，请根据上述提示修正后重试" << endl;
    }

	return result;
}

void BackendCore::Logout() {
	if (isLoggedIn_) {
		cout << "用户 " << currentUser_.username << " 注销" << endl;
	}
// 重置用户状态
	isLoggedIn_ = false;
	currentUser_ = UserInfo();
	examManager_.CancelExam();// 取消进行中的考试

	questionService_.SetCurrentUser("");// 清空题目服务的用户设置
}

bool BackendCore::GenerateExam(const std::string& userType, int questionCount) {
// 检查登录状态和题目数量范围
    if (!isLoggedIn_ || questionCount < 10 || questionCount > 30) {
        return false;
	}
// 生成题目列表
	auto questions = questionService_.GenerateQuestions(userType, questionCount);
	if (questions.empty()) {
		return false;
	}
// 开始新考试
	return examManager_.StartNewExam(questions, userType);
}

Question BackendCore::GetCurrentQuestion() {
	return examManager_.GetCurrentQuestion();
}

int BackendCore::GetCurrentQuestionIndex() {
	return examManager_.GetCurrentQuestionIndex();
}

int BackendCore::GetTotalQuestions() {
	return examManager_.GetTotalQuestions();
}

bool BackendCore::SubmitAnswer(int answer) {
	return examManager_.SubmitAnswer(answer);
}

bool BackendCore::MoveToNextQuestion() {
	return examManager_.MoveToNextQuestion();
}

bool BackendCore::MoveToPreviousQuestion() {
	return examManager_.MoveToPreviousQuestion();
}

ExamResult BackendCore::SubmitExam() {
	return examManager_.SubmitExam();
}

void BackendCore::CancelExam() {
	examManager_.CancelExam();
}

bool BackendCore::IsLoggedIn() {
	return isLoggedIn_;
}

UserInfo BackendCore::GetCurrentUser() {
	return currentUser_;
}

std::string BackendCore::GetCurrentUserType() {
	return currentUser_.userType;
}

void BackendCore::SetCurrentUserType(const std::string& userType) {
	if (isLoggedIn_ && (userType == "小学" || userType == "初中" || userType == "高中")) {
		currentUser_.userType = userType;
		// 更新持久化存储
		userManager_.UpdateUserType(currentUser_.username, userType);
		cout << "用户类型已更新为: " << userType << endl;
	}
}

bool BackendCore::ValidatePassword(const std::string& password) {
	if (password.length() < 6 || password.length() > 10) {
		return false;
	}

	bool hasUpper = false, hasLower = false, hasDigit = false;
	for (char c : password) {
		if (isupper(c)) hasUpper = true;
		else if (islower(c)) hasLower = true;
		else if (isdigit(c)) hasDigit = true;
	}

	return hasUpper && hasLower && hasDigit;
}

bool BackendCore::IsValidEmail(const std::string& email) {
	// 简单的邮箱格式验证
	size_t atPos = email.find('@');
	if (atPos == string::npos || atPos == 0) return false;

	size_t dotPos = email.find('.', atPos);
	if (dotPos == string::npos || dotPos == atPos + 1) return false;

	return dotPos < email.length() - 1;
}
