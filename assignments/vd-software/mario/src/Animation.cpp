#include "Animation.hpp"

Animation::Animation()
    : mFrameDuration(0.f)
    , mElapsedTime(0.f)
    , mCurrentFrame(0)
    , mLooping(true)
    , mFinished(false)
{
}

Animation::Animation(const sf::Texture& texture, int frameWidth, int frameHeight, int numFrames, float frameDuration)
    : mFrameDuration(frameDuration)
    , mElapsedTime(0.f)
    , mCurrentFrame(0)
    , mLooping(true)
    , mFinished(false)
{
    // Create frame rectangles
    for (int i = 0; i < numFrames; ++i) {
        sf::IntRect frame(i * frameWidth, 0, frameWidth, frameHeight);
        mFrames.push_back(frame);
    }
}

void Animation::update(float deltaTime) {
    if (mFinished) {
        return;
    }
    
    mElapsedTime += deltaTime;
    
    if (mElapsedTime >= mFrameDuration) {
        mElapsedTime = 0.f;
        ++mCurrentFrame;
        
        if (mCurrentFrame >= mFrames.size()) {
            mCurrentFrame = 0;
            
            if (!mLooping) {
                mFinished = true;
                --mCurrentFrame;
            }
        }
    }
}

void Animation::applyToSprite(sf::Sprite& sprite) const {
    if (!mFrames.empty()) {
        sprite.setTextureRect(mFrames[mCurrentFrame]);
    }
}

void Animation::restart() {
    mCurrentFrame = 0;
    mElapsedTime = 0.f;
    mFinished = false;
}

bool Animation::isFinished() const {
    return mFinished;
}

void Animation::setLooping(bool looping) {
    mLooping = looping;
}
