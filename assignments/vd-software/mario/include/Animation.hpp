#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation();
    Animation(const sf::Texture& texture, int frameWidth, int frameHeight, int numFrames, float frameDuration);
    
    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite) const;
    void restart();
    bool isFinished() const;
    
    void setLooping(bool looping);

private:
    std::vector<sf::IntRect> mFrames;
    float mFrameDuration;
    float mElapsedTime;
    int mCurrentFrame;
    bool mLooping;
    bool mFinished;
};
