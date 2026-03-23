#ifndef PAIR_PROJECT2_0_SRC_BACKEND_UTILS_FILEHELPER_H_
#define PAIR_PROJECT2_0_SRC_BACKEND_UTILS_FILEHELPER_H_

#include <string>
#include <vector>

class FileHelper {
	public:
		/**
		* @brief 检查文件是否存在
		* @param filename 文件名
		* @return bool 文件存在返回true，否则返回false
		*/
		static bool FileExists(const std::string& filename);

		/**
		* @brief 创建目录
		* @param path 目录路径
		* @return bool 创建成功返回true，否则返回false
		*/
		static bool CreateDirectoryW(const std::string& path);

		/**
		* @brief 读取文件内容
		* @param filename 文件名
		* @return std::string 文件内容字符串
		*/
		static std::string ReadFile(const std::string& filename);

		/**
		* @brief 写入内容到文件
		* @param filename 文件名
		* @param content 要写入的内容
		* @return bool 写入成功返回true，否则返回false
		*/
		static bool WriteFile(const std::string& filename, const std::string& content);

		/**
		* @brief 按行读取文件
		* @param filename 文件名
		* @return std::vector<std::string> 包含每行内容的字符串向量
		*/
		static std::vector<std::string> ReadLines(const std::string& filename);

		/**
		* @brief 按行写入文件
		* @param filename 文件名
		* @param lines 包含每行内容的字符串向量
		* @return bool 写入成功返回true，否则返回false
		*/
		static bool WriteLines(const std::string& filename, const std::vector<std::string>& lines);

		/**
		* @brief 生成带时间戳的文件名
		* @param prefix 文件名前缀
		* @param extension 文件扩展名
		* @return std::string 生成的文件名字符串
		*/
		static std::string GenerateTimestampFilename(const std::string& prefix, const std::string& extension);
};

#endif  // PAIR_PROJECT2_0_SRC_BACKEND_UTILS_FILEHELPER_H_
