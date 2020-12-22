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

    APIConnector();

    ~APIConnector();
};

#endif