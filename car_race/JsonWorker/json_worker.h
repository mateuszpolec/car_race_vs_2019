#include <json/json.h>
#include <iostream>


/**
* Class JSONWorker
* Processing the JSON passed from other classes/functions
*/

class JSONWorker {


    private:
        JSONCPP_STRING err; // error if something wents wrong
        Json::StreamWriterBuilder builder;


	public:
        /**
        * Function getJsonFromTokenString
        * @param rawJson - string json object passed from anywhere in project
        * @return token - authentication token for user to keep up communication with API
        */
		std::string getJsonTokenFromString(const std::string rawJson) {
            Json::Value root; // root value for processing json string to structure
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

        //std::string prepareDataForAPIUpdate(std::string token, sf::Vector2f playerPosition) {
        //    Json::Value root; // root value for processing json string to structure
        //    const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        //    root["token"] = token;
        //    root["x_position"] = playerPosition.x;
        //    root["y_position"] = playerPosition.y;
        //    const std::string api_data = Json::writeString(builder, root);
        //    return api_data;
        //}

        
};