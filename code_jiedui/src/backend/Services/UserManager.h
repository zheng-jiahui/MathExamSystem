#ifndef PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_USERMANAGER_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_USERMANAGER_H_

#include "../Models/UserInfo.h"
#include "../Utils/FileHelper.h"
#include "../Utils/StringHelper.h"

#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <curl/curl.h>

class UserManager {
	public:
		/**
		* @brief 构造函数
		* @param dataFile 用户数据文件路径
		*/
		explicit UserManager(const std::string& dataFile);

		/**
		* @brief 析构函数
		*/
		~UserManager();


		/**
		* @brief 注册用户（第一步：发送验证码）
                * @param username 用户名
                * @param email 邮箱地址
		* @param outRegCode 输出注册码的引用
		* @return bool 注册成功返回true，否则返回false
		*/
                bool RegisterUser(const std::string& username,const std::string& email, std::string& outRegCode);

		/**
		* @brief 完成注册（第二步：验证信息并创建账户）
                * @param username 用户名
		* @param email 邮箱地址
		* @param regCode 注册码
		* @param password 密码
		* @param confirmPassword 确认密码
		* @param userType 用户类型
		* @return bool 注册完成返回true，否则返回false
		*/
                bool CompleteRegistrationWithType(const std::string& username,const std::string& email, const std::string& regCode,
		                                  const std::string& password, const std::string& confirmPassword,
		                                  const std::string& userType);

		/**
		* @brief 用户认证
		* @param username 用户名
		* @param password 密码
		* @param outUser 输出用户信息的引用
		* @return bool 认证成功返回true，否则返回false
		*/
		bool Authenticate(const std::string& username, const std::string& password, UserInfo& outUser);

		/**
		* @brief 修改密码
		* @param username 用户名
		* @param oldPassword 旧密码
		* @param newPassword 新密码
		* @param confirmNewPassword 确认新密码
		* @return bool 修改成功返回true，否则返回false
		*/
		bool ChangePassword(const std::string& username, const std::string& oldPassword,
		                    const std::string& newPassword, const std::string& confirmNewPassword);

		/**
		* @brief 检查用户是否存在
		* @param username 用户名
		* @return bool 存在返回true，否则返回false
		*/
		bool UserExists(const std::string& username);

		/**
		* @brief 检查邮箱是否存在
		* @param email 邮箱地址
		* @return bool 存在返回true，否则返回false
		*/
		bool EmailExists(const std::string& email);

		/**
		* @brief 更新用户类型
		* @param username 用户名
		* @param userType 用户类型
		* @return bool 更新成功返回true，否则返回false
		*/
		bool UpdateUserType(const std::string& username, const std::string& userType);

		/**
		* @brief 验证注册输入
                * @param username 用户名
		* @param email 邮箱地址
		* @param regCode 注册码
		* @param password 密码
		* @param confirmPassword 确认密码
		* @param userType 用户类型
		* @return bool 输入有效返回true，否则返回false
		*/
                bool ValidateRegistrationInput(const std::string& username,const std::string& email, const std::string& regCode,
		                               const std::string& password, const std::string& confirmPassword,
		                               const std::string& userType);

		/**
		* @brief 验证用户类型
		* @param userType 用户类型
		* @return bool 有效返回true，否则返回false
		*/
		bool ValidateUserType(const std::string& userType);

		/**
		* @brief 验证密码匹配
		* @param password 密码
		* @param confirmPassword 确认密码
		* @return bool 匹配返回true，否则返回false
		*/
		bool ValidatePasswordMatch(const std::string& password, const std::string& confirmPassword);

		/**
		* @brief 验证密码复杂度
		* @param password 密码
		* @return bool 符合复杂度要求返回true，否则返回false
		*/
		bool ValidatePasswordComplexity(const std::string& password);

		/**
		* @brief 验证注册码
                * @param username 用户名
		* @param email 邮箱地址
		* @param regCode 注册码
		* @return bool 有效返回true，否则返回false
		*/
                bool ValidateRegistrationCode(const std::string& username,const std::string& email, const std::string& regCode);

		/**
		* @brief 生成唯一用户名
		* @param email 邮箱地址
		* @return string 生成的用户名
		*/
		std::string GenerateUniqueUsername(const std::string& email);

		/**
		* @brief 创建用户账户
		* @param email 邮箱地址
		* @param username 用户名
		* @param password 密码
		* @param userType 用户类型
		* @return bool 创建成功返回true，否则返回false
		*/
		bool CreateUserAccount(const std::string& email, const std::string& username,
		                       const std::string& password, const std::string& userType);

		/**
		* @brief 验证密码修改输入
		* @param username 用户名
		* @param oldPassword 旧密码
		* @param newPassword 新密码
		* @param confirmNewPassword 确认新密码
		* @return bool 输入有效返回true，否则返回false
		*/
		bool ValidatePasswordChangeInput(const std::string& username, const std::string& oldPassword,
		                                 const std::string& newPassword, const std::string& confirmNewPassword);

		/**
		* @brief 验证新密码匹配
		* @param newPassword 新密码
		* @param confirmNewPassword 确认新密码
		* @return bool 匹配返回true，否则返回false
		*/
		bool ValidateNewPasswordMatch(const std::string& newPassword, const std::string& confirmNewPassword);

		/**
		* @brief 验证新密码复杂度
		* @param newPassword 新密码
		* @return bool 符合复杂度要求返回true，否则返回false
		*/
		bool ValidateNewPasswordComplexity(const std::string& newPassword);

		/**
		* @brief 验证旧密码
		* @param username 用户名
		* @param oldPassword 旧密码
		* @return bool 验证成功返回true，否则返回false
		*/
		bool ValidateOldPassword(const std::string& username, const std::string& oldPassword);

		/**
		* @brief 验证新旧密码是否相同
		* @param oldPassword 旧密码
		* @param newPassword 新密码
		* @return bool 相同返回true，否则返回false
		*/
		bool ValidatePasswordNotSame(const std::string& oldPassword, const std::string& newPassword);

		/**
		* @brief 更新用户密码
		* @param username 用户名
		* @param newPassword 新密码
		* @return bool 更新成功返回true，否则返回false
		*/
		bool UpdateUserPassword(const std::string& username, const std::string& newPassword);

	private:
		/**
		* @brief 加载用户数据
		*/
		void LoadUsers();

		/**
		* @brief 保存用户数据
		*/
		void SaveUsers();

		/**
		* @brief 生成注册码
		* @return string 生成的注册码
		*/
		std::string GenerateRegistrationCode();

		/**
		* @brief 验证密码格式
		* @param password 密码
		* @return bool 格式正确返回true，否则返回false
		*/
		bool ValidatePassword(const std::string& password);

		std::string dataFile_;
		std::vector<UserInfo> users_;
		std::map<std::string, std::string> pendingRegistrations_; // email -> regCode
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_SERVICES_USERMANAGER_H_
