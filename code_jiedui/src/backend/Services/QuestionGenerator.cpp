#include "QuestionGenerator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// PrimaryGenerator 的静态成员初始化
mt19937 PrimaryGenerator::gen;

void PrimaryGenerator::InitRandom() {
	// 使用高精度时间戳作为种子
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	gen.seed(seed);
}

vector<int> PrimaryGenerator::GenerateOperands(int count) {
	uniform_int_distribution<> num_dist(1, 100);// 1-100范围内的操作数
	vector<int> operands;
	for (int i = 0; i < count; i++) {
		operands.push_back(num_dist(gen));
	}
	return operands;
}

vector<char> PrimaryGenerator::GenerateOperators(int count) {
	uniform_int_distribution<> op_type_dist(1, 3);// 四种基本运算符
	vector<char> operators;
	for (int i = 0; i < count; i++) {
		int op_type = op_type_dist(gen);
		if (op_type == 0) operators.push_back('+');
		else if (op_type == 1) operators.push_back('-');
		else if (op_type == 2) operators.push_back('*');
		else operators.push_back('/');
	}
	return operators;
}

string PrimaryGenerator::BuildQuestion(const vector<int>& operands,
                                       const vector<char>& operators,
                                       bool use_brackets) {
	string question;

	if (use_brackets && operands.size() > 2) {
		// 随机选择括号位置
		uniform_int_distribution<> bracket_pos_dist(0, operands.size() - 2);
		int bracket_pos = bracket_pos_dist(gen);

		// 构建带括号的表达式
		for (int i = 0; i < operands.size(); i++) {
			if (i == bracket_pos) question += "(";
			question += to_string(operands[i]);
			if (i == bracket_pos + 1) question += ")";
			if (i < operands.size() - 1) question += " " + string(1, operators[i]) + " ";
		}
	} else {
// 构建普通表达式
		for (int i = 0; i < operands.size(); i++) {
			question += to_string(operands[i]);
			if (i < operands.size() - 1) question += " " + string(1, operators[i]) + " ";
		}
	}

	return question;
}

string PrimaryGenerator::GenerateQuestion() {
	InitRandom();
	uniform_int_distribution<> op_count_dist(2, 5);// 2-5个操作数
	uniform_int_distribution<> bracket_dist(0, 1);// 50%概率使用括号

	string question;
	int result;
	do {
		int operands_count = op_count_dist(gen);
		vector<char> operators = GenerateOperators(operands_count - 1);
		vector<int> operands = GenerateOperands(operands_count);

		// 简单顺序计算（不考虑括号优先级，仅用于检查负数）
		result = operands[0];
		for (int i = 0; i < operators.size(); i++) {
			if (operators[i] == '+') result += operands[i + 1];
			else if (operators[i] == '-') result -= operands[i + 1];
			else if (operators[i] == '*') result *= operands[i + 1];
			else if (operators[i] == '/') {
				if (operands[i + 1] != 0) result /= operands[i + 1];
			}
		}

		bool use_brackets = (bracket_dist(gen) == 0 && operands_count > 2);
		question = BuildQuestion(operands, operators, use_brackets);
	} while (result < 0);// 确保结果非负

	return question + " = ";
}

// JuniorGenerator 的静态成员初始化
mt19937 JuniorGenerator::gen;

void JuniorGenerator::InitRandom() {
	// 使用高精度时间戳作为种子
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	gen.seed(seed);
}

string JuniorGenerator::GenerateSpecialOperator() {
	uniform_int_distribution<> special_dist(0, 1);// 平方或平方根
	uniform_int_distribution<> square_dist(1, 20);// 平方数范围
	uniform_int_distribution<> sqrt_dist(1, 10);// 平方根数范围

	if (special_dist(gen) == 0) {
		int num = square_dist(gen);
		return to_string(num) + "²";// 平方表示
	} else {
		int num = sqrt_dist(gen);
		return "√" + to_string(num * num);// 平方根，确保结果为整数
	}
}

string JuniorGenerator::BuildQuestion(bool& has_special_op, int operands_count) {
	uniform_int_distribution<> num_dist(1, 100);
	uniform_int_distribution<> op_type_dist(0, 3);
	uniform_int_distribution<> prob_dist(0, 1);

	string question;
	for (int i = 0; i < operands_count; i++) {
		// 随机决定是否插入特殊运算符
		if (!has_special_op && (i == operands_count - 1 || prob_dist(gen) == 0)) {
			question += GenerateSpecialOperator();
			has_special_op = true;
		} else {
			question += to_string(num_dist(gen));
		}

		if (i < operands_count - 1) {
			int op_type = op_type_dist(gen);
			if (op_type == 0) question += " + ";
			else if (op_type == 1) question += " - ";
			else if (op_type == 2) question += " * ";
			else question += " / ";
		}
	}
	return question;
}

string JuniorGenerator::GenerateQuestion() {
	InitRandom();
	uniform_int_distribution<> op_count_dist(2, 4);

	bool has_special_op = false;
	int operands_count = op_count_dist(gen);
	string question = BuildQuestion(has_special_op, operands_count);
	// 确保至少包含一个特殊运算符
	if (!has_special_op) {
		question = GenerateSpecialOperator() + " + " + question;
	}

	return question + " = ";
}

// SeniorGenerator 的静态成员初始化
mt19937 SeniorGenerator::gen;

void SeniorGenerator::InitRandom() {
	// 使用高精度时间戳作为种子
	auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
	gen.seed(seed);
}

string SeniorGenerator::GenerateTrigFunction() {
	uniform_int_distribution<> trig_dist(0, 2);// 三种三角函数
	uniform_int_distribution<> angle_dist(1, 12);// 15°的倍数

	int trig_type = trig_dist(gen);
	int angle = angle_dist(gen) * 15;// 15°, 30°, 45°... 180°

	if (trig_type == 0) return "sin" + to_string(angle) + "°";
	else if (trig_type == 1) return "cos" + to_string(angle) + "°";
	else return "tan" + to_string(angle) + "°";
}

string SeniorGenerator::BuildQuestion(bool& has_trig, int operands_count) {
	uniform_int_distribution<> num_dist(1, 100);
	uniform_int_distribution<> op_type_dist(0, 3);
	uniform_int_distribution<> prob_dist(0, 1);

	string question;
	for (int i = 0; i < operands_count; i++) {
		// 随机决定是否插入三角函数
		if (!has_trig && (i == operands_count - 1 || prob_dist(gen) == 0)) {
			question += GenerateTrigFunction();
			has_trig = true;
		} else {
			question += to_string(num_dist(gen));
		}

		if (i < operands_count - 1) {
			int op_type = op_type_dist(gen);
			if (op_type == 0) question += " + ";
			else if (op_type == 1) question += " - ";
			else if (op_type == 2) question += " * ";
			else question += " / ";
		}
	}
	return question;
}

string SeniorGenerator::GenerateQuestion() {
	InitRandom();
	uniform_int_distribution<> op_count_dist(2, 4);

	bool has_trig = false;
	int operands_count = op_count_dist(gen);
	string question = BuildQuestion(has_trig, operands_count);

	// 确保至少包含一个三角函数
	if (!has_trig) {
		question = GenerateTrigFunction() + " + " + question;
	}

	return question + " = ";
}
