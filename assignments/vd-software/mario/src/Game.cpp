#include "Game.hpp"
#include <iostream>

Game::Game()
    : mWindow(sf::VideoMode(800, 600), "Super Mario Clone")
    , mIsPlaying(false)
    , mGameCompleted(false)
    , mUsingSoundEffects(true)
{
    mWindow.setFramerateLimit(60);
    
    // Load resources
    loadTextures();
    loadSounds();
    
    // Create game objects
    mMario = std::make_unique<Mario>(mTextures);
    mLevel = std::make_unique<Level>(mTextures);
    
    // Set initial Mario position
    mMario->setPosition(100.f, 300.f);
    
    // Start background music
    mBackgroundMusic.setLoop(true);
    mBackgroundMusic.play();
}

Game::~Game() {
    // Clean up resources if needed
}

void Game::run() {
    sf::Clock clock;
    float deltaTime = 0.0f;
    
    mIsPlaying = true;
    
    // Main game loop
    while (mWindow.isOpen() && mIsPlaying) {
        deltaTime = clock.restart().asSeconds();
        
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
        
        // Handle keyboard input for Mario
        mMario->handleInput(event);
    }
    
    // Handle controller input
    handleControllerInput();
}

void Game::update(float deltaTime) {
    // Update game objects
    mMario->update(deltaTime);
    
    // Check collisions between Mario and level elements
    mLevel->checkCollisions(*mMario);
    
    // Check if Mario collected coins
    if (mMario->collectedCoin() && mUsingSoundEffects) {
        mCoinSound.play();
    }
    
    // Check if Mario got a power-up
    if (mMario->poweredUp() && mUsingSoundEffects) {
        mPowerupSound.play();
    }
    
    // Check if Mario jumped
    if (mMario->isJumping() && mUsingSoundEffects) {
        mJumpSound.play();
    }
    
    // Check if level is completed
    if (mLevel->isCompleted()) {
        mGameCompleted = true;
        mIsPlaying = false;
    }
}

void Game::render() {
    mWindow.clear(sf::Color(107, 140, 255)); // Sky blue background
    
    // Draw level
    mLevel->render(mWindow);
    
    // Draw Mario
    mMario->render(mWindow);
    
    // Draw UI elements like score
    
    // Display game completed message if needed
    if (mGameCompleted) {
        sf::Text gameCompletedText;
        sf::Font font;
        if (font.loadFromFile("resources/arial.ttf")) {
            gameCompletedText.setFont(font);
            gameCompletedText.setString("Level Completed!");
            gameCompletedText.setCharacterSize(48);
            gameCompletedText.setFillColor(sf::Color::White);
            gameCompletedText.setPosition(
                mWindow.getSize().x / 2 - gameCompletedText.getGlobalBounds().width / 2,
                mWindow.getSize().y / 2 - gameCompletedText.getGlobalBounds().height / 2
            );
            mWindow.draw(gameCompletedText);
        }
    }
    
    mWindow.display();
}

void Game::handleControllerInput() {
    // Check for controller connection
    if (sf::Joystick::isConnected(0)) {
        float axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        
        if (axisX < -30.f) {
            mMario->moveLeft();
        }
        else if (axisX > 30.f) {
            mMario->moveRight();
        }
        else {
            mMario->stopMoving();
        }
        
        // Jump with A button (button 0)
        if (sf::Joystick::isButtonPressed(0, 0)) {
            mMario->jump();
        }
    }
}

void Game::loadTextures() {
    // Load Mario textures
    sf::Texture marioTexture;
    if (marioTexture.loadFromFile("resources/mario_sprites.png")) {
        mTextures["mario"] = marioTexture;
    }
    else {
        std::cerr << "Failed to load mario_sprites.png" << std::endl;
    }
    
    // Load block textures
    sf::Texture blockTexture;
    if (blockTexture.loadFromFile("resources/blocks.png")) {
        mTextures["blocks"] = blockTexture;
    }
    else {
        std::cerr << "Failed to load blocks.png" << std::endl;
    }
    
    // Load coin texture
    sf::Texture coinTexture;
    if (coinTexture.loadFromFile("resources/coin.png")) {
        mTextures["coin"] = coinTexture;
    }
    else {
        std::cerr << "Failed to load coin.png" << std::endl;
    }
    
    // Load mushroom texture
    sf::Texture mushroomTexture;
    if (mushroomTexture.loadFromFile("resources/mushroom.png")) {
        mTextures["mushroom"] = mushroomTexture;
    }
    else {
        std::cerr << "Failed to load mushroom.png" << std::endl;
    }
}

void Game::loadSounds() {
    // Load sound effects
    try {
        // Load jump sound
        sf::SoundBuffer jumpBuffer;
        if (jumpBuffer.loadFromFile("resources/jump_sound.wav")) {
            mSoundBuffers["jump"] = jumpBuffer;
            mJumpSound.setBuffer(mSoundBuffers["jump"]);
        }
        else {
            std::cerr << "Failed to load jump_sound.wav" << std::endl;
            mUsingSoundEffects = false;
        }
        
        // Load coin sound
        sf::SoundBuffer coinBuffer;
        if (coinBuffer.loadFromFile("resources/coin_sound.wav")) {
            mSoundBuffers["coin"] = coinBuffer;
            mCoinSound.setBuffer(mSoundBuffers["coin"]);
        }
        else {
            std::cerr << "Failed to load coin_sound.wav" << std::endl;
            mUsingSoundEffects = false;
        }
        
        // Load powerup sound
        sf::SoundBuffer powerupBuffer;
        if (powerupBuffer.loadFromFile("resources/powerup_sound.wav")) {
            mSoundBuffers["powerup"] = powerupBuffer;
            mPowerupSound.setBuffer(mSoundBuffers["powerup"]);
        }
        else {
            std::cerr << "Failed to load powerup_sound.wav" << std::endl;
            mUsingSoundEffects = false;
        }
        
        // Load background music
        if (!mBackgroundMusic.openFromFile("resources/background_music.wav")) {
            std::cerr << "Failed to load background_music.wav" << std::endl;
            mUsingSoundEffects = false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading sound resources: " << e.what() << std::endl;
        mUsingSoundEffects = false;
    }
}
