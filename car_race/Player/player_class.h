#include <iostream>

class Player {
    int x;
    int y;

public:
    Player(int x_position, int y_position) {
        x = x_position;
        y = y_position;
    };

    void getMyPosition() {
        std::cout << "My position is: " << x << y;
    }
};