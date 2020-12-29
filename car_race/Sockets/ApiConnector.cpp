#include "ApiConnector.h"
#include <SFML/Network.hpp>
#include <SFML/Network/Http.hpp>
#include <iostream>


APIConnector::APIConnector() : 
    jsonWorker(new JSONWorker()) {}

APIConnector::~APIConnector() {
    delete this->jsonWorker;
}

std::string APIConnector::getAuthToken() {
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
            const std::string token = this->jsonWorker->getJsonTokenFromString(rawJson);
            FileWorker::saveTokenToFile(token); //Save token to file
            return token;
        }
        else
        {
            return "";
        }
    }
}