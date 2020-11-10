#ifndef API_CONNECTOR_H
#define API_CONNECTOR_H

#include <SFML/Network.hpp>
#include <SFML/Network/Http.hpp>
#include <iostream>
#include <json/json.h>
#include "../FileWorker/file_worker.h"
#include "../JsonWorker/json_worker.h"

/**
* Class APIConnector - Inherits from JSONWorker
* Made it possible to communicate with API
*/

class APIConnector : FileWorker, public virtual JSONWorker {

private:
    sf::Http http;
    JSONCPP_STRING err;
    Json::Value root;
    Json::StreamWriterBuilder builder;
    JSONWorker* jsonWorker;
public:
    /**
    *
    * Function getAuthToken
    * @param -
    * @return token - Token for Player Class to continue communication with api
    * 
    */
    std::string getAuthToken();

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

    APIConnector();

    ~APIConnector();
};

#endif