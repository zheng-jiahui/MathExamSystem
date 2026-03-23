#ifndef PAIR_PROJECT2_0_SRC_BACKEND_UTILS_STRINGHELPER_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_UTILS_STRINGHELPER_H_

#include <string>
#include <vector>

class StringHelper {
	public:
		/**
		* @brief 分割字符串
		* @param str 输入字符串
		* @param delimiter 分隔符
		* @return vector<string> 分割后的字符串向量
		*/
		static std::vector<std::string> Split(const std::string& str, char delimiter);

		/**
		* @brief 去除字符串首尾空白字符
		* @param str 输入字符串
		* @return string 去除空白后的字符串
		*/
		static std::string Trim(const std::string& str);

		/**
		* @brief 检查字符串是否以指定前缀开头
		* @param str 输入字符串
		* @param prefix 前缀字符串
		* @return bool 以指定前缀开头返回true，否则返回false
		*/
		static bool StartsWith(const std::string& str, const std::string& prefix);

		/**
		* @brief 检查字符串是否以指定后缀结尾
		* @param str 输入字符串
		* @param suffix 后缀字符串
		* @return bool 以指定后缀结尾返回true，否则返回false
		*/
		static bool EndsWith(const std::string& str, const std::string& suffix);

		/**
		* @brief 检查字符串是否包含子串
		* @param str 输入字符串
		* @param substr 子串
		* @return bool 包含子串返回true，否则返回false
		*/
		static bool Contains(const std::string& str, const std::string& substr);

		/**
		* @brief 转换为小写
		* @param str 输入字符串
		* @return string 小写字符串
		*/
		static std::string ToLower(const std::string& str);

		/**
		* @brief 转换为大写
		* @param str 输入字符串
		* @return string 大写字符串
		*/
		static std::string ToUpper(const std::string& str);

		/**
		* @brief 验证邮箱格式
		* @param email 邮箱字符串
		* @return bool 格式正确返回true，否则返回false
		*/
		static bool IsValidEmail(const std::string& email);

		/**
		* @brief 生成随机字符串
		* @param length 字符串长度
		* @return string 随机字符串
		*/
		static std::string GenerateRandomString(int length);
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_UTILS_STRINGHELPER_H_
