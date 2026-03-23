#include "StringHelper.h"
#include <algorithm>
#include <cctype>
#include <random>
#include <sstream>
#include <chrono>  // 添加这个头文件

using namespace std;

vector<string> StringHelper::Split(const std::string& str, char delimiter) {
	vector<string> tokens;
	stringstream ss(str);
	string token;

	// 使用getline按分隔符分割字符串
	while (getline(ss, token, delimiter)) {
		if (!token.empty()) {
			tokens.push_back(token);// 只添加非空token
		}
	}

	return tokens;
}

string StringHelper::Trim(const std::string& str) {
	// 找到第一个非空白字符的位置
	size_t start = str.find_first_not_of(" \t\n\r");
	if (start == string::npos) return "";// 全是空白字符

	// 找到最后一个非空白字符的位置
	size_t end = str.find_last_not_of(" \t\n\r");
	return str.substr(start, end - start + 1);// 返回去除首尾空白后的子串
}

bool StringHelper::StartsWith(const std::string& str, const std::string& prefix) {
	return str.size() >= prefix.size() &&
	       str.compare(0, prefix.size(), prefix) == 0;// 比较前prefix.length()个字符
}

bool StringHelper::EndsWith(const std::string& str, const std::string& suffix) {
	return str.size() >= suffix.size() &&
	       str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;// 比较后suffix.length()个字符
}

bool StringHelper::Contains(const std::string& str, const std::string& substr) {
	return str.find(substr) != string::npos;// 使用find查找子串
}

string StringHelper::ToLower(const std::string& str) {
	string result = str;
	// 使用transform和tolower转换所有字符为小写
	transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

string StringHelper::ToUpper(const std::string& str) {
	string result = str;
	// 使用transform和toupper转换所有字符为大写
	transform(result.begin(), result.end(), result.begin(), ::toupper);
	return result;
}

bool StringHelper::IsValidEmail(const std::string& email) {
	// 简单的邮箱格式验证
	size_t at_pos = email.find('@');
	if (at_pos == string::npos || at_pos == 0) return false;// 必须包含@且不在开头

	size_t dot_pos = email.find('.', at_pos);
	if (dot_pos == string::npos || dot_pos == at_pos + 1) return false;// @后必须有.且不能紧挨着

	return dot_pos < email.length() - 1;// .后必须有字符
}

string StringHelper::GenerateRandomString(int length) {
	static const char alphanum[] =
	    "0123456789"
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	    "abcdefghijklmnopqrstuvwxyz";// 可用的字符集

#if defined(_WIN32)
	// Windows特定：使用CryptGenRandom或时间种子
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	mt19937 gen(seed);
#endif

	uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

	string result;
	result.reserve(length);// 预分配空间

	// 随机选择字符构建字符串
	for (int i = 0; i < length; ++i) {
		result += alphanum[dis(gen)];
	}

	return result;
}
