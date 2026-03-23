#include "FileHelper.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

using namespace std;

bool FileHelper::FileExists(const std::string& filename) {
	ifstream file(filename);
	return file.good();// 检查文件是否成功打开
}

bool FileHelper::CreateDirectoryW(const std::string& path) {
#ifdef _WIN32
	return _mkdir(path.c_str()) == 0;// Windows创建目录
#else
	return mkdir(path.c_str(), 0755) == 0;// Linux/Mac创建目录
#endif
}

string FileHelper::ReadFile(const std::string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		return "";// 文件打开失败返回空字符串
	}

  // 使用stringstream读取整个文件内容
	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

bool FileHelper::WriteFile(const std::string& filename, const std::string& content) {
	ofstream file(filename);
	if (!file.is_open()) {
		return false;// 文件创建失败
	}

	file << content;// 写入内容
	return true;
}

vector<string> FileHelper::ReadLines(const std::string& filename) {
	vector<string> lines;
	ifstream file(filename);
	if (!file.is_open()) {
		return lines;// 返回空向量
	}

	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			lines.push_back(line);// 只添加非空行
		}
	}

	return lines;
}

bool FileHelper::WriteLines(const std::string& filename, const std::vector<std::string>& lines) {
	ofstream file(filename);
	if (!file.is_open()) {
		return false;
	}

  // 逐行写入，每行末尾添加换行符
	for (const auto& line : lines) {
		file << line << "\n";
	}

	return true;
}

string FileHelper::GenerateTimestampFilename(const std::string& prefix, const std::string& extension) {
	time_t now = time(0);
	tm* ltm = localtime(&now);// 获取本地时间

  // 生成格式：前缀_年-月-日_时-分-秒.扩展名
	stringstream ss;
	ss << prefix << "_"
	   << 1900 + ltm->tm_year << "-"
	   << 1 + ltm->tm_mon << "-"
	   << ltm->tm_mday << "_"
	   << ltm->tm_hour << "-"
	   << ltm->tm_min << "-"
	   << ltm->tm_sec
	   << extension;

	return ss.str();
}
