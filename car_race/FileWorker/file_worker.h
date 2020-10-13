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
		void saveTokenToFile(std::string token);
		
		/**
		* getTokenFromFile
		* get token from file, if it exists if not return empty string
		* @return token - API Auth Hashed token
		*/
		std::string getTokenFromFile();
};