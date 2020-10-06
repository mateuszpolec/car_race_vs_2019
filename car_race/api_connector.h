#include <SFML/Network.hpp>
#include <SFML/Network/Http.hpp>
#include <iostream>
#include <json/json.h>
#include "json_worker.h"


/**
* Class APIConnector - Inherits from JSONWorker
* Made it possible to communicate with API
* 
*/

class APIConnector : JSONWorker {
public:

    /**
    *
    * Function getAuthToken
    * @param -
    * @return - Token for Player Class to continue communication with api
    * 
    */
    void getAuthToken() {
        // Create a new HTTP client
        sf::Http http;
        JSONCPP_STRING err;
        Json::Value root;
        // Host for localhost, REMBEMER to turn on Django API
        http.setHost("127.0.0.1", 8000);
        // Prepare request for auth
        sf::Http::Request request("/api/auth/");
        // Send the request
        sf::Http::Response response = http.sendRequest(request);
        // Check the status code and display the result
        sf::Http::Response::Status status = response.getStatus();
        if (status == sf::Http::Response::Ok)
        {
            const std::string rawJson = response.getBody();
            // Pass the response to json_worker class
            std::cout << getJsonTokenFromString(rawJson) << std::endl;
        }
        else
        {
            std::cout << "Error " << status << std::endl;
        }
    }
};