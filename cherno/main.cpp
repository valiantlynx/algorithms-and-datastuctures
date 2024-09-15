#include <iostream>

#define LOG(x) std::cout << x << std::endl

class Player {
public:
    int x, y;
    int speed;

    void Move(int xa, int ya) {
        x += xa * speed;
        y += ya * speed;
    }
};

struct Data {
    int x, y;

    int Add(int x, int y) {
        return x + y;
    }
};


int main() {
    Player player;
    player.Move(1000, 1000);
    
    LOG(player.x);
    Data data;
    int result = data.Add(4, 3);

    LOG(result);
    
    std::cin.get();
}