#include <SFML/Network.hpp>
#include <SFML/Network/Http.hpp>
#include <iostream>
#include <json/json.h>

class APIConnector {
public:

    void getAuthToken() {
        // Create a new HTTP client
        sf::Http http;
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
            std::cout << rawJson << std::endl;
            std::cout << "[api_connector.h] Passing JSON to const string" << std::endl;
        }
        else
        {
            std::cout << "Error " << status << std::endl;
        }
    }
};