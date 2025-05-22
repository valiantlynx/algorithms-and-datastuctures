#pragma once

#include "Entity.hpp"

class Mushroom : public Entity {
public:
    Mushroom(const sf::Texture& texture);
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    void collect();
    bool isCollected() const;
    void setDirection(float direction);

private:
    const float MOVEMENT_SPEED = 100.f;
    bool mCollected;
    float mDirection;
};
