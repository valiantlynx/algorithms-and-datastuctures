#include "Mushroom.hpp"

Mushroom::Mushroom(const sf::Texture& texture)
    : mCollected(false)
    , mDirection(1.f)  // Moving right by default
{
    mSprite.setTexture(texture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void Mushroom::update(float deltaTime) {
    if (!mCollected) {
        // Move horizontally
        mVelocity.x = MOVEMENT_SPEED * mDirection;
        
        // Apply gravity
        mVelocity.y += 980.f * deltaTime;
        
        // Update position
        mPosition += mVelocity * deltaTime;
        mSprite.setPosition(mPosition);
    }
}

void Mushroom::render(sf::RenderWindow& window) {
    if (!mCollected) {
        window.draw(mSprite);
    }
}

void Mushroom::collect() {
    mCollected = true;
}

bool Mushroom::isCollected() const {
    return mCollected;
}

void Mushroom::setDirection(float direction) {
    mDirection = direction;
}
