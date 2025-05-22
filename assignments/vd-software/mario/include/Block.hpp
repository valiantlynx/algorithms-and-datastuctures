#pragma once

#include "Entity.hpp"
#include <functional>

enum class BlockType {
    Solid,  // Cannot be broken
    Brick,  // Can be broken
    Question // Contains power-up or coin
};

class Block : public Entity {
public:
    Block(const sf::Texture& texture, BlockType type);
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    BlockType getType() const;
    void hit(std::function<void()> onBreak = nullptr, std::function<void()> onReleasePowerup = nullptr);
    bool isHit() const;
    bool hasItem() const;
    void setHasItem(bool hasItem);

private:
    BlockType mType;
    bool mIsHit;
    bool mHasItem;
    float mHitAnimationTime;
    float mInitialY;
    
    const float HIT_ANIMATION_DURATION = 0.3f;
    const float HIT_ANIMATION_HEIGHT = 10.f;
};
