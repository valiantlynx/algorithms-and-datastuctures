#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <map>
#include <string>
#include "Mario.hpp"
#include "Level.hpp"

class Game {
public:
    Game();
    ~Game();
    
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void handleControllerInput();

    // Game window
    sf::RenderWindow mWindow;
    
    // Game assets
    std::map<std::string, sf::Texture> mTextures;
    std::map<std::string, sf::SoundBuffer> mSoundBuffers;
    
    // Game sounds
    sf::Sound mJumpSound;
    sf::Sound mCoinSound;
    sf::Sound mPowerupSound;
    sf::Music mBackgroundMusic;
    
    // Game objects
    std::unique_ptr<Mario> mMario;
    std::unique_ptr<Level> mLevel;
    
    // Game state
    bool mIsPlaying;
    bool mGameCompleted;
    bool mUsingSoundEffects;
    
    // Load resources
    void loadTextures();
    void loadSounds();
};
