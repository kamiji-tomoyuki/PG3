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
	// --- �ǂݍ��� ---
	std::string fileName = "PG3_2024_03_02.txt";
	std::ifstream file(fileName);
	if (!file.is_open()) {
		std::cerr << "�t�@�C�����J���܂���: " << fileName << std::endl;
		return 1;
	}

	// --- �ǂݎ�� ---
	std::vector<std::string> mails;
	std::string line;

	while (std::getline(file, line)) {
		// "[]" �폜
		line.erase(std::remove(line.begin(), line.end(), '['), line.end());
		line.erase(std::remove(line.begin(), line.end(), ']'), line.end());

		// "," �ŕ���
		std::stringstream comma(line);
		std::string mail;
		while (std::getline(comma, mail, ',')) {
			mail.erase(std::remove(mail.begin(), mail.end(), '\"'), mail.end());
			mails.push_back(mail);
		}
	}

	file.close();
	std::sort(mails.begin(), mails.end());

	// --- �`�� ---
	std::cout << "���ёւ������I" << std::endl;
	for (const auto& email : mails) {
		std::cout << email << std::endl;
	}

	return 0;
}