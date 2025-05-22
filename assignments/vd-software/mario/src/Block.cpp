#include "Block.hpp"
#include <cmath>

Block::Block(const sf::Texture& texture, BlockType type)
    : mType(type)
    , mIsHit(false)
    , mHasItem(type == BlockType::Question)
    , mHitAnimationTime(0.f)
    , mInitialY(0.f)
{
    mSprite.setTexture(texture);
    
    // Set texture rectangle based on block type
    switch (type) {
        case BlockType::Solid:
            mSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
            break;
        case BlockType::Brick:
            mSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
            break;
        case BlockType::Question:
            mSprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
            break;
    }
}

void Block::update(float deltaTime) {
    if (mIsHit) {
        mHitAnimationTime += deltaTime;
        
        if (mHitAnimationTime < HIT_ANIMATION_DURATION) {
            // Move up and down during hit animation
            float offset = HIT_ANIMATION_HEIGHT * std::sin(mHitAnimationTime / HIT_ANIMATION_DURATION * 3.14159f);
            mSprite.setPosition(mPosition.x, mInitialY - offset);
        }
        else {
            mHitAnimationTime = 0.f;
            mIsHit = false;
            mSprite.setPosition(mPosition);
            
            // Change question block to empty block after hit
            if (mType == BlockType::Question && !mHasItem) {
                mSprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
            }
        }
    }
}

void Block::render(sf::RenderWindow& window) {
    window.draw(mSprite);
}

BlockType Block::getType() const {
    return mType;
}

void Block::hit(std::function<void()> onBreak, std::function<void()> onReleasePowerup) {
    if (!mIsHit) {
        mIsHit = true;
        mInitialY = mPosition.y;
        
        if (mType == BlockType::Question && mHasItem) {
            mHasItem = false;
            if (onReleasePowerup) {
                onReleasePowerup();
            }
        }
        else if (mType == BlockType::Brick) {
            if (onBreak) {
                onBreak();
            }
        }
    }
}

bool Block::isHit() const {
    return mIsHit;
}

bool Block::hasItem() const {
    return mHasItem;
}

void Block::setHasItem(bool hasItem) {
    mHasItem = hasItem;
}
