#include "Mario.hpp"
#include <iostream>

Mario::Mario(const std::map<std::string, sf::Texture>& textures)
    : mIsMovingLeft(false)
    , mIsMovingRight(false)
    , mIsJumping(false)
    , mIsOnGround(false)
    , mJustJumped(false)
    , mCoinCollected(false)
    , mPoweredUp(false)
    , mFacingRight(true)
    , mState(MarioState::Small)
    , mCurrentAnimation(MarioAnimation::Idle)
    , mScore(0)
{
    // Check if textures exist and set sprite texture
    if (textures.find("mario") != textures.end()) {
        mSprite.setTexture(textures.at("mario"));
        initAnimations(textures.at("mario"));
    }
    else {
        std::cerr << "Mario texture not found!" << std::endl;
    }
    
    // Set initial sprite properties
    mSprite.setPosition(mPosition);
    switchAnimation(MarioAnimation::Idle);
}

void Mario::update(float deltaTime) {
    // Reset state flags
    mJustJumped = false;
    mCoinCollected = false;
    mPoweredUp = false;
    
    // Apply gravity
    applyGravity(deltaTime);
    
    // Handle horizontal movement
    mVelocity.x = 0.f;
    
    if (mIsMovingLeft) {
        mVelocity.x = -MOVEMENT_SPEED;
        mFacingRight = false;
    }
    if (mIsMovingRight) {
        mVelocity.x = MOVEMENT_SPEED;
        mFacingRight = true;
    }
    
    // Update position
    mPosition += mVelocity * deltaTime;
    mSprite.setPosition(mPosition);
    
    // Update animation
    updateAnimation(deltaTime);
    
    // Flip sprite based on direction
    if (mFacingRight) {
        mSprite.setScale(1.f, 1.f);
    }
    else {
        mSprite.setScale(-1.f, 1.f);
        // Adjust position for flipped sprite
        mSprite.setPosition(mPosition.x + mSprite.getGlobalBounds().width, mPosition.y);
    }
}

void Mario::render(sf::RenderWindow& window) {
    window.draw(mSprite);
}

void Mario::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            moveLeft();
        }
        else if (event.key.code == sf::Keyboard::Right) {
            moveRight();
        }
        else if (event.key.code == sf::Keyboard::Space) {
            jump();
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Left && mIsMovingLeft) {
            mIsMovingLeft = false;
        }
        else if (event.key.code == sf::Keyboard::Right && mIsMovingRight) {
            mIsMovingRight = false;
        }
    }
}

void Mario::moveLeft() {
    mIsMovingLeft = true;
    if (mIsOnGround) {
        switchAnimation(MarioAnimation::Running);
    }
}

void Mario::moveRight() {
    mIsMovingRight = true;
    if (mIsOnGround) {
        switchAnimation(MarioAnimation::Running);
    }
}

void Mario::stopMoving() {
    mIsMovingLeft = false;
    mIsMovingRight = false;
    if (mIsOnGround) {
        switchAnimation(MarioAnimation::Idle);
    }
}

void Mario::jump() {
    if (mIsOnGround) {
        mVelocity.y = JUMP_FORCE;
        mIsJumping = true;
        mIsOnGround = false;
        mJustJumped = true;
        switchAnimation(MarioAnimation::Jumping);
    }
}

bool Mario::isJumping() const {
    return mJustJumped;
}

bool Mario::isOnGround() const {
    return mIsOnGround;
}

void Mario::setOnGround(bool onGround) {
    mIsOnGround = onGround;
    if (onGround) {
        mIsJumping = false;
        if (!mIsMovingLeft && !mIsMovingRight) {
            switchAnimation(MarioAnimation::Idle);
        }
        else {
            switchAnimation(MarioAnimation::Running);
        }
    }
}

bool Mario::collectedCoin() {
    return mCoinCollected;
}

bool Mario::poweredUp() {
    return mPoweredUp;
}

MarioState Mario::getState() const {
    return mState;
}

void Mario::setState(MarioState state) {
    if (mState != state) {
        mState = state;
        if (state == MarioState::Big) {
            mPoweredUp = true;
        }
        // Update animation based on new state
        switchAnimation(mCurrentAnimation);
    }
}

void Mario::applyGravity(float deltaTime) {
    if (!mIsOnGround) {
        mVelocity.y += GRAVITY * deltaTime;
    }
}

void Mario::incrementScore(int points) {
    mScore += points;
    mCoinCollected = true;
}

int Mario::getScore() const {
    return mScore;
}

void Mario::initAnimations(const sf::Texture& texture) {
    // Small Mario animations
    // Idle animation
    mAnimations[MarioAnimation::Idle] = Animation(texture, 16, 16, 1, 0.1f);
    
    // Running animation
    mAnimations[MarioAnimation::Running] = Animation(texture, 16, 16, 3, 0.1f);
    
    // Jumping animation
    mAnimations[MarioAnimation::Jumping] = Animation(texture, 16, 16, 1, 0.1f);
    
    // Big Mario animations
    // Idle animation
    mBigAnimations[MarioAnimation::Idle] = Animation(texture, 16, 32, 1, 0.1f);
    
    // Running animation
    mBigAnimations[MarioAnimation::Running] = Animation(texture, 16, 32, 3, 0.1f);
    
    // Jumping animation
    mBigAnimations[MarioAnimation::Jumping] = Animation(texture, 16, 32, 1, 0.1f);
}

void Mario::updateAnimation(float deltaTime) {
    auto& animations = (mState == MarioState::Small) ? mAnimations : mBigAnimations;
    animations[mCurrentAnimation].update(deltaTime);
    animations[mCurrentAnimation].applyToSprite(mSprite);
}

void Mario::switchAnimation(MarioAnimation animation) {
    if (mCurrentAnimation != animation) {
        mCurrentAnimation = animation;
        
        auto& animations = (mState == MarioState::Small) ? mAnimations : mBigAnimations;
        animations[mCurrentAnimation].restart();
    }
}
