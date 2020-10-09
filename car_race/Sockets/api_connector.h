#include <SFML/Network.hpp>
#include <SFML/Network/Http.hpp>
#include <iostream>
#include <json/json.h>
#include "JsonWorker/json_worker.h"
#include "FileWorker/file_worker.h"



/**
* Class APIConnector - Inherits from JSONWorker
* Made it possible to communicate with API
*/

class APIConnector : JSONWorker, FileWorker {

private:
    sf::Http http;
    JSONCPP_STRING err;
    Json::Value root;
    Json::StreamWriterBuilder builder;
public:

    /**
    *
    * Function getAuthToken
    * @param -
    * @return token - Token for Player Class to continue communication with api
    * 
    */
    auto getAuthToken() {
        // Host for localhost, REMBEMER to turn on Django API
        const std::string token = FileWorker::getTokenFromFile();
        if (token != "") {
            return token;
        }
        else {
            http.setHost("127.0.0.1", 8000);
            sf::Http::Request request("/api/auth/");
            sf::Http::Response response = http.sendRequest(request);
            sf::Http::Response::Status status = response.getStatus();
            if (status == sf::Http::Response::Ok)
            {
                const std::string rawJson = response.getBody();
                // Pass the response to json_worker class
                const std::string token = getJsonTokenFromString(rawJson);
                FileWorker::saveTokenToFile(token); //Save token to file
                return token;
            }
            else
            {
                std::cout << "Error " << status << std::endl;
            }
        }
    }

    /**
    * TODO: Create function, that save player information in api
    */
    //void sendPlayerInformation(std::string token, sf::Vector2f playerPosition) {
    //    http.setHost("127.0.0.1", 8000);
    //    std::string api_data = JSONWorker::prepareDataForAPIUpdate(token, playerPosition);
    //    sf::Http::Request request;
    //    request.setMethod(sf::Http::Request::Put);
    //    request.setUri("/api/player/");
    //    request.setHttpVersion(1, 1);
    //    request.setField("Content-Type", "application/json");
    //    request.setBody(api_data);
    //    std::cout << api_data << std::endl;
    //    http.sendRequest(request);
    //}
};