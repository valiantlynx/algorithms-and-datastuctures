#include <iostream>

#define LOG(x) std::cout << x << std::endl

class Player {
public:
    int x, y;
    int speed;

};

int main() {
    Player player;
    player.x = 5;
    player.y = 5;

    LOG(player.x);
    
    std::cin.get();
}