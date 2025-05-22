#pragma once

#include "Entity.hpp"
#include "Animation.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <map>
#include <string>

enum class MarioState {
    Small,
    Big
};

enum class MarioAnimation {
    Idle,
    Running,
    Jumping
};

class Mario : public Entity {
public:
    explicit Mario(const std::map<std::string, sf::Texture>& textures);
    
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    void handleInput(const sf::Event& event);
    
    void moveLeft();
    void moveRight();
    void stopMoving();
    void jump();
    
    bool isJumping() const;
    bool isOnGround() const;
    void setOnGround(bool onGround);
    
    bool collectedCoin();
    bool poweredUp();
    
    MarioState getState() const;
    void setState(MarioState state);
    
    void applyGravity(float deltaTime);
    void incrementScore(int points);
    int getScore() const;

private:
    const float MOVEMENT_SPEED = 200.f;
    const float JUMP_FORCE = -450.f;
    const float GRAVITY = 980.f;
    
    bool mIsMovingLeft;
    bool mIsMovingRight;
    bool mIsJumping;
    bool mIsOnGround;
    bool mJustJumped;
    bool mCoinCollected;
    bool mPoweredUp;
    bool mFacingRight;
    
    MarioState mState;
    MarioAnimation mCurrentAnimation;
    
    int mScore;
    
    void initAnimations(const sf::Texture& texture);
    void updateAnimation(float deltaTime);
    void switchAnimation(MarioAnimation animation);
    
    std::map<MarioAnimation, Animation> mAnimations;
    std::map<MarioAnimation, Animation> mBigAnimations;
};
