#include <iostream>


/**
* Class Player - handle information about player
* 
*/
class Player {
    int x;
    int y;
    std::string token;

public:
    /**
    * Constructor
    * @param x_position - X-axis player position
    * @param y_position - Y-axis player position
    * @param authtoken - Authentication token for API communication
    */
    Player(int x_position, int y_position, std::string authtoken) {
        token = authtoken;
        x = x_position;
        y = y_position;
    };

    void getMyPosition() {
        std::cout << "My position is: " << x << y;
    }
};