#include <fstream>
#include <iostream>

/**
* Class FileWorker - makes it easier to work with token file
*/
class FileWorker {
	public:
		/**
		* saveTokenToFile
		* saves passed token to file
		* @param token - API Auth Hashed Token
		*/
		void saveTokenToFile(std::string token) {
			const std::string filename("./token.txt");
			std::ofstream stream(filename.c_str());

			if (stream) {
				stream << token << std::endl;
				stream << "Please, do not touch this hash it will remove your progress in game" << std::endl;
			}
		}
		
		/**
		* getTokenFromFile
		* get token from file, if it exists if not return empty string
		* @return token - API Auth Hashed token
		*/
		std::string getTokenFromFile() {
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
};