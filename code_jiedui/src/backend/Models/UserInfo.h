#ifndef PAIR_PROJECT2_0_SRC_BACKEND_MODELS_USERINFO_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_MODELS_USERINFO_H_

#include <string>

/**
 * @brief 用户信息数据结构
 */
struct UserInfo {
	std::string username;// 用户名
	std::string email;// 邮箱地址
	std::string userType;// 用户类型（"小学"/"初中"/"高中"）
	std::string password;// 密码（通常为加密后的）

	/**
	 * @brief 默认构造函数
	 */
	UserInfo() = default;

	/**
	 * @brief 参数化构造函数
	 * @param uname 用户名
	 * @param mail 邮箱地址
	 * @param type 用户类型
	 * @param pwd 密码
	 */
	UserInfo(const std::string& uname, const std::string& mail,
	         const std::string& type, const std::string& pwd)
		: username(uname), email(mail), userType(type), password(pwd) {}
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_MODELS_USERINFO_H_
