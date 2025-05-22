#include "Coin.hpp"

Coin::Coin(const sf::Texture& texture)
    : mCollected(false)
{
    mSprite.setTexture(texture);
    
    // Create spinning animation
    mAnimation = Animation(texture, 16, 16, 4, 0.1f);
}

void Coin::update(float deltaTime) {
    if (!mCollected) {
        mAnimation.update(deltaTime);
        mAnimation.applyToSprite(mSprite);
        mSprite.setPosition(mPosition);
    }
}

void Coin::render(sf::RenderWindow& window) {
    if (!mCollected) {
        window.draw(mSprite);
    }
}

void Coin::collect() {
    mCollected = true;
}

bool Coin::isCollected() const {
    return mCollected;
}
