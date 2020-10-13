#include <fstream>
#include <iostream>
#include <string>
#include "file_worker.h"


void FileWorker::saveTokenToFile(std::string token) {
	const std::string filename("./token.txt");
	std::ofstream stream(filename.c_str());

	if (stream) {
		stream << token << std::endl;
		stream << "Please, do not touch this hash it will remove your progress in game" << std::endl;
	}
}

std::string FileWorker::getTokenFromFile() {
	std::ifstream file("./token.txt");

	if (file) {
		std::string token;
		getline(file, token);
		return token;
	}
	else {
		return "";
	}
}
