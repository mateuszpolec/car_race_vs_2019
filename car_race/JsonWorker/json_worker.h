#ifndef JSON_WORKER_H
#define JSON_WORKER_H

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
        std::string getJsonTokenFromString(const std::string rawJson);
        
};

#endif