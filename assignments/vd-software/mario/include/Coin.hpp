#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class Coin : public Entity {
public:
    Coin(const sf::Texture& texture);
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    void collect();
    bool isCollected() const;
    
    static const int COIN_VALUE = 100;

private:
    Animation mAnimation;
    bool mCollected;
};
