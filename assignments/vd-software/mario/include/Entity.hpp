#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();
    virtual ~Entity() = default;
    
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    
    bool intersects(const Entity& other) const;

protected:
    sf::Vector2f mPosition;
    sf::Vector2f mVelocity;
    sf::Sprite mSprite;
    bool mActive;
};
