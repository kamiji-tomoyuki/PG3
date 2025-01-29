#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
using namespace std;

int main() {
	// --- 読み込み ---
	std::string fileName = "PG3_2024_03_02.txt";
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "ファイルが開けません: " << fileName << std::endl;
		return 1;
	}

	// --- 読み取り ---
	std::vector<std::string> mails;
	std::string line;

	while (std::getline(file, line)) {
		// "[]" 削除
		line.erase(std::remove(line.begin(), line.end(), '['), line.end());
		line.erase(std::remove(line.begin(), line.end(), ']'), line.end());

		// "," で分割
		std::stringstream comma(line);
		std::string mail;
		while (std::getline(comma, mail, ',')) {
			mail.erase(std::remove(mail.begin(), mail.end(), '\"'), mail.end());
			mails.push_back(mail);
		}
	}

	file.close();
	std::sort(mails.begin(), mails.end());

	// --- 描画 ---
	std::cout << "並び替え完了！" << std::endl;
	for (const auto& email : mails) {
		std::cout << email << std::endl;
	}

	return 0;
}