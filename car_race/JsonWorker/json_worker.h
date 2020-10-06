#include <json/json.h>
#include <iostream>


/**
* Class JSONWorker
* Processing the JSON passed from other classes/functions
*/

class JSONWorker {

    private:
        Json::Value root; // root value for processing json string to structure
        JSONCPP_STRING err; // error if something wents wrong

	public:
        /**
        * Function getJsonFromTokenString
        * @param rawJson - string json object passed from anywhere in project
        * @return token - authentication token for user to keep up communication with API
        */
		auto getJsonTokenFromString(const std::string rawJson) {
            const auto rawJsonLength = static_cast<int>(rawJson.length());
            Json::CharReaderBuilder builder;
            const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
            if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,
                &err)) {
                std::cout << "error" << std::endl;
            }
            const std::string token = root["token"].asString();
            return token;

		}
};