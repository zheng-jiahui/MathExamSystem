#include "UserManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Windows下使用libcurl的正确方式
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

#include <curl/curl.h>

using namespace std;

// 上传数据结构，用于邮件发送
struct UploadData {
	std::string data;// 邮件内容数据
	size_t pos = 0;// 当前读取位置
};

// libcurl读取回调函数，用于邮件内容上传
static size_t read_callback(char* buffer, size_t size, size_t nitems, void* userdata) {
	auto* upload = static_cast<UploadData*>(userdata);
	size_t buffer_size = size * nitems;

	// 检查是否已读取完所有数据
	if (upload->pos >= upload->data.size()) {
		return 0;
	}

	// 计算剩余数据量和本次要拷贝的数据量
	size_t remain = upload->data.size() - upload->pos;
	size_t copy_size = std::min(remain, buffer_size);

	// 拷贝数据到缓冲区
	memcpy(buffer, upload->data.data() + upload->pos, copy_size);
	upload->pos += copy_size;
	return copy_size;
}

UserManager::UserManager(const std::string& dataFile) : dataFile_(dataFile) {
	LoadUsers();// 构造函数中加载用户数据
}

UserManager::~UserManager() {
	SaveUsers();// 析构函数中保存用户数据
}

void UserManager::LoadUsers() {
	users_.clear();

	auto lines = FileHelper::ReadLines(dataFile_);
	// 解析每行用户数据
	for (const auto& line : lines) {
		auto parts = StringHelper::Split(line, '|');// 使用|分隔符
		if (parts.size() >= 4) {
			// 创建用户对象并添加到列表
			users_.emplace_back(parts[0], parts[1], parts[2], parts[3]);
		}
	}
}

void UserManager::SaveUsers() {
	vector<string> lines;
	// 将用户数据序列化为字符串
	for (const auto& user : users_) {
		stringstream ss;
		ss << user.username << "|" << user.email << "|" << user.userType << "|" << user.password;
		lines.push_back(ss.str());
	}

	FileHelper::WriteLines(dataFile_, lines);// 写入文件
}

// 初始化Winsock（仅限Windows系统）
void InitializeWinsock() {
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		throw std::runtime_error("❌ 初始化Winsock失败");
	}
#endif
}

// 清理Winsock资源（仅限Windows系统）
void CleanupWinsock() {
#ifdef _WIN32
	WSACleanup();
#endif
}

// 初始化CURL库并返回CURL指针
CURL* InitializeCurl() {
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl = curl_easy_init();
	if (!curl) {
		throw std::runtime_error("❌ 初始化curl失败");
	}
	return curl;
}

// 设置CURL的各种选项，包括目标邮件地址和邮件内容
void SetCurlOptions(CURL* curl, const std::string& email, const std::string& regCode, struct curl_slist*& rcpt_list, UploadData*& upload) {
	rcpt_list = curl_slist_append(nullptr, email.c_str());
	// 构造邮件内容
	upload = new UploadData();
	upload->data = "To: " + email + "\r\nFrom: <panxy2005@hnu.edu.cn>\r\nSubject: 【数学考试系统】注册验证码\r\n\r\n您的注册验证码是：" + regCode + "\r\n请在24小时内完成注册。\r\n";

	// 设置SMTP服务器和身份验证信息
	curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.exmail.qq.com:465");
	curl_easy_setopt(curl, CURLOPT_USERNAME, "panxy2005@hnu.edu.cn");
	curl_easy_setopt(curl, CURLOPT_PASSWORD, "3724303Xj");
	curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<panxy2005@hnu.edu.cn>");
	curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, rcpt_list);
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
	curl_easy_setopt(curl, CURLOPT_READDATA, upload);
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

#ifdef _WIN32
	// 在Windows环境中关闭SSL验证（仅用于开发环境）
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#else
	// 在其他平台启用SSL
	curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
#endif
}

// 发送注册邮件的主函数
bool SendRegistrationEmail(const std::string& email, const std::string& regCode) {
	try {
		InitializeWinsock();// 初始化网络库
		CURL* curl = InitializeCurl();// 初始化CURL库

		struct curl_slist* rcpt_list = nullptr;
		UploadData* upload = nullptr;
		SetCurlOptions(curl, email, regCode, rcpt_list, upload);// 设置CURL参数

		CURLcode res = curl_easy_perform(curl);// 执行邮件发送
		bool success = (res == CURLE_OK);

		if (!success) {
			// 错误处理
			cerr << "❌ 邮件发送失败: " << curl_easy_strerror(res) << endl;
			if (res == CURLE_LOGIN_DENIED) cerr << "⚠️ 登录被拒绝，请检查邮箱授权码\n";
			else if (res == CURLE_COULDNT_CONNECT) cerr << "⚠️ 无法连接到SMTP服务器\n";
			else if (res == CURLE_SSL_CONNECT_ERROR) cerr << "⚠️ SSL连接错误，请检查SSL设置\n";
		} else {
			cout << "✅ 注册码已成功发送至邮箱：" << email << endl;
		}

		// 清理分配的资源
		if (rcpt_list) curl_slist_free_all(rcpt_list);
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		CleanupWinsock();// 清理网络库

		delete upload;
		return success;
	} catch (const std::exception& e) {
		cerr << e.what() << endl;
		return false;
	}
}

// 用户注册第一步：验证用户名和邮箱并发送注册码
bool UserManager::RegisterUser(const std::string& username, const std::string& email, std::string& outRegCode) {
    // 验证用户名格式
    if (username.empty()) {
        cerr << "用户名不能为空\n";
        return false;
    }

    // 验证邮箱格式
    if (email.find('@') == string::npos) {
        cerr << "邮箱格式错误\n";
        return false;
    }

    // 检查用户名是否已存在
    if (UserExists(username)) {
        cerr << "用户名已被占用\n";
        return false;
    }

    // 检查邮箱是否已注册
    if (EmailExists(email)) {
        cerr << "邮箱已注册\n";
        return false;
    }

    // 生成注册码并保存到待注册列表
    outRegCode = GenerateRegistrationCode();
    // 使用用户名和邮箱的组合作为键，确保唯一性
    string key = username + "|" + email;
    pendingRegistrations_[key] = outRegCode;

    // 发送注册邮件
    return SendRegistrationEmail(email, outRegCode);
}

bool UserManager::CompleteRegistrationWithType(const std::string& username, const std::string& email, const std::string& regCode,
        const std::string& password, const std::string& confirmPassword,
        const std::string& userType) {
    // 验证所有注册输入
    if (!ValidateRegistrationInput(username, email, regCode, password, confirmPassword, userType)) {
        return false;
    }

    // 创建用户账户
    return CreateUserAccount(email, username, password, userType);
}

bool UserManager::ValidateRegistrationInput(const std::string& username, const std::string& email, const std::string& regCode,
        const std::string& password, const std::string& confirmPassword,
        const std::string& userType) {
    // 依次验证各项输入
    if (!ValidateUserType(userType)) return false;
    if (!ValidatePasswordMatch(password, confirmPassword)) return false;
    if (!ValidatePasswordComplexity(password)) return false;
    if (!ValidateRegistrationCode(username, email, regCode)) return false;
    return true;
}

bool UserManager::ValidateRegistrationCode(const std::string& username, const std::string& email, const std::string& regCode) {
    // 验证注册码是否匹配
    string key = username + "|" + email;
    auto it = pendingRegistrations_.find(key);
    if (it == pendingRegistrations_.end()) {
        cerr << "❌ 该用户名和邮箱未申请注册或注册码已过期" << endl;
        return false;
    }

    if (it->second != regCode) {
        cerr << "❌ 注册码不正确" << endl;
        return false;
    }

    return true;
}

bool UserManager::ValidatePasswordMatch(const std::string& password, const std::string& confirmPassword) {
	// 验证两次输入的密码是否一致
	if (password != confirmPassword) {
		cerr << "❌ 两次输入的密码不匹配" << endl;
		return false;
	}
	return true;
}

bool UserManager::ValidatePasswordComplexity(const std::string& password) {
	// 验证密码长度
	if (password.length() < 6) {
		cerr << "❌ 密码长度不足：需要至少6个字符" << endl;
		return false;
	}

	if (password.length() > 10) {
		cerr << "❌ 密码长度过长：最多10个字符" << endl;
		return false;
	}

	// 检查密码复杂度要求
	bool hasUpper = false, hasLower = false, hasDigit = false;
	for (char c : password) {
		if (isupper(c)) hasUpper = true;
		else if (islower(c)) hasLower = true;
		else if (isdigit(c)) hasDigit = true;
	}

	// 提供详细的错误信息
	if (!hasUpper) cerr << "❌ 密码必须包含至少一个大写字母" << endl;
	if (!hasLower) cerr << "❌ 密码必须包含至少一个小写字母" << endl;
	if (!hasDigit) cerr << "❌ 密码必须包含至少一个数字" << endl;

	return hasUpper && hasLower && hasDigit;
}

bool UserManager::ValidateUserType(const std::string& userType) {
    // 验证用户类型是否合法
    if (userType != "小学" && userType != "初中" && userType != "高中") {
        cerr << "❌ 用户类型必须是小学、初中或高中" << endl;
        return false;
    }
    return true;
}

string UserManager::GenerateUniqueUsername(const std::string& email) {
	// 基于邮箱前缀生成用户名
	string baseUsername = email.substr(0, email.find('@'));
	string username = baseUsername;
	int counter = 1;

	// 如果用户名已存在，添加数字后缀
	while (UserExists(username)) {
		username = baseUsername + to_string(counter++);
		if (counter > 100) {
			cerr << "❌ 无法生成唯一用户名，请使用其他邮箱" << endl;
			return "";
		}
	}

	return username;
}

bool UserManager::CreateUserAccount(const std::string& email, const std::string& username,
                                    const std::string& password, const std::string& userType) {
    // 创建新用户并添加到列表
    users_.emplace_back(username, email, userType, password);

    // 移除待注册记录
    string key = username + "|" + email;
    auto it = pendingRegistrations_.find(key);
    if (it != pendingRegistrations_.end()) {
        pendingRegistrations_.erase(it);
    }

    SaveUsers();// 保存到文件

    cout << "✅ 注册完成！" << endl;
    cout << "   用户名: " << username << endl;
    cout << "   用户类型: " << userType << endl;
    cout << "   邮箱: " << email << endl;
    cout << "   请使用此用户名和密码登录" << endl;

    return true;
}

bool UserManager::Authenticate(const std::string& username, const std::string& password, UserInfo& outUser) {
	// 检查用户名是否为空
	if (username.empty()) {
		cerr << "❌ 用户名不能为空" << endl;
		return false;
	}

	// 检查密码是否为空
	if (password.empty()) {
		cerr << "❌ 密码不能为空" << endl;
		return false;
	}

	// 查找用户
	for (const auto& user : users_) {
		if (user.username == username) {
			// 找到用户，检查密码
			if (user.password == password) {
				outUser = user;
				cout << "✅ 登录成功！欢迎 " << username << endl;
				return true;
			} else {
				// 密码错误
				cerr << "❌ 密码错误" << endl;
				cerr << "提示：如果您忘记密码，请联系管理员重置" << endl;
				return false;
			}
		}
	}

	// 用户不存在
	cerr << "❌ 用户 '" << username << "' 不存在" << endl;
	cerr << "提示：请检查用户名拼写或先注册新账户" << endl;

	return false;
}

bool UserManager::ChangePassword(const std::string& username, const std::string& oldPassword,
                                 const std::string& newPassword, const std::string& confirmNewPassword) {
	// 验证密码修改输入
	if (!ValidatePasswordChangeInput(username, oldPassword, newPassword, confirmNewPassword)) {
		return false;
	}

	return UpdateUserPassword(username, newPassword);
}

bool UserManager::ValidatePasswordChangeInput(const std::string& username, const std::string& oldPassword,
        const std::string& newPassword, const std::string& confirmNewPassword) {
	// 依次验证各项输入
	if (!ValidateNewPasswordMatch(newPassword, confirmNewPassword)) return false;
	if (!ValidateNewPasswordComplexity(newPassword)) return false;
	if (!ValidateOldPassword(username, oldPassword)) return false;
	if (!ValidatePasswordNotSame(oldPassword, newPassword)) return false;
	return true;
}

bool UserManager::ValidateNewPasswordMatch(const std::string& newPassword, const std::string& confirmNewPassword) {
	// 验证新密码是否匹配
	if (newPassword != confirmNewPassword) {
        cerr << "两次输入的新密码不匹配" << endl;
		return false;
	}
	return true;
}

bool UserManager::ValidateNewPasswordComplexity(const std::string& newPassword) {
	// 验证新密码复杂度（与注册时相同）
	if (newPassword.length() < 6) {
        cerr << " 新密码长度不足：需要至少6个字符" << endl;
		return false;
	}

	if (newPassword.length() > 10) {
        cerr << "新密码长度过长：最多10个字符" << endl;
		return false;
	}

	bool hasUpper = false, hasLower = false, hasDigit = false;
	for (char c : newPassword) {
		if (isupper(c)) hasUpper = true;
		else if (islower(c)) hasLower = true;
		else if (isdigit(c)) hasDigit = true;
	}

    if (!hasUpper) cerr << "新密码必须包含至少一个大写字母" << endl;
    if (!hasLower) cerr << "新密码必须包含至少一个小写字母" << endl;
    if (!hasDigit) cerr << "新密码必须包含至少一个数字" << endl;

	return hasUpper && hasLower && hasDigit;
}

bool UserManager::ValidateOldPassword(const std::string& username, const std::string& oldPassword) {
	// 验证旧密码是否正确
	for (const auto& user : users_) {
		if (user.username == username) {
			if (user.password == oldPassword) {
				return true;
			} else {
                cerr << "原密码不正确" << endl;
                //cerr << "如果您忘记原密码，请联系管理员" << endl;
				return false;
			}
		}
	}

    cerr << "用户不存在" << endl;
	return false;
}

bool UserManager::ValidatePasswordNotSame(const std::string& oldPassword, const std::string& newPassword) {
	// 验证新旧密码是否不同
	if (oldPassword == newPassword) {
        cerr << "新密码不能与旧密码相同" << endl;
		return false;
	}
	return true;
}

bool UserManager::UpdateUserPassword(const std::string& username, const std::string& newPassword) {
	// 更新用户密码
	for (auto& user : users_) {
		if (user.username == username) {
			user.password = newPassword;
			SaveUsers();// 保存更改
            cout << " 密码修改成功！" << endl;
			cout << "下次登录请使用新密码" << endl;
			return true;
		}
	}

    cerr << "更新密码时发生错误" << endl;
	return false;
}

bool UserManager::UserExists(const std::string& username) {
	// 检查用户名是否存在
	return any_of(users_.begin(), users_.end(),
	[&](const UserInfo& user) {
		return user.username == username;
	});
}

bool UserManager::EmailExists(const std::string& email) {
	// 检查邮箱是否存在
	return any_of(users_.begin(), users_.end(),
	[&](const UserInfo& user) {
		return user.email == email;
	});
}

string UserManager::GenerateRegistrationCode() {
	// 生成8位随机注册码
	return StringHelper::GenerateRandomString(8);
}

bool UserManager::ValidatePassword(const std::string& password) {
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

bool UserManager::UpdateUserType(const std::string& username, const std::string& userType) {
	// 更新用户类型
	for (auto& user : users_) {
		if (user.username == username) {
			user.userType = userType;
			SaveUsers();// 保存更改
			return true;
		}
	}
	return false;
}
