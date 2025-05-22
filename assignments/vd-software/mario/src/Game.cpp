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
    
    // Start background music only if loaded successfully
    if (mUsingSoundEffects && mBackgroundMusic.getStatus() != sf::Music::Status::Playing) {
        mBackgroundMusic.setLoop(true);
        mBackgroundMusic.play();
    }
    
    // Log initialization
    std::cout << "Game initialized. Window size: 800x600" << std::endl;
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
        std::cout << "Successfully loaded mario_sprites.png" << std::endl;
    }
    else {
        std::cerr << "Failed to load mario_sprites.png - creating placeholder texture" << std::endl;
        // Create a placeholder texture for Mario if the file is missing
        sf::Image placeholderImage;
        placeholderImage.create(16, 16, sf::Color::Red);
        sf::Texture placeholder;
        placeholder.loadFromImage(placeholderImage);
        mTextures["mario"] = placeholder;
    }
    
    // Load block textures
    sf::Texture blockTexture;
    if (blockTexture.loadFromFile("resources/blocks.png")) {
        mTextures["blocks"] = blockTexture;
        std::cout << "Successfully loaded blocks.png" << std::endl;
    }
    else {
        std::cerr << "Failed to load blocks.png - creating placeholder texture" << std::endl;
        // Create a placeholder texture for blocks
        sf::Image placeholderImage;
        placeholderImage.create(64, 16, sf::Color::Blue);
        // Create different block types in the placeholder
        for (int i = 0; i < 4; i++) {
            for (int x = 0; x < 16; x++) {
                for (int y = 0; y < 16; y++) {
                    if (i == 0) { // Solid block
                        placeholderImage.setPixel(i*16 + x, y, sf::Color(150, 75, 0));
                    } else if (i == 1) { // Brick block
                        if ((x < 2 || x > 14) || (y < 2 || y > 14)) {
                            placeholderImage.setPixel(i*16 + x, y, sf::Color(150, 75, 0));
                        } else {
                            placeholderImage.setPixel(i*16 + x, y, sf::Color(200, 100, 0));
                        }
                    } else if (i == 2) { // Question block
                        placeholderImage.setPixel(i*16 + x, y, sf::Color(255, 215, 0));
                    } else { // Empty block
                        placeholderImage.setPixel(i*16 + x, y, sf::Color(100, 100, 100));
                    }
                }
            }
        }
        sf::Texture placeholder;
        placeholder.loadFromImage(placeholderImage);
        mTextures["blocks"] = placeholder;
    }
    
    // Load coin texture
    sf::Texture coinTexture;
    if (coinTexture.loadFromFile("resources/coin.png")) {
        mTextures["coin"] = coinTexture;
        std::cout << "Successfully loaded coin.png" << std::endl;
    }
    else {
        std::cerr << "Failed to load coin.png - creating placeholder texture" << std::endl;
        // Create a placeholder texture for coins
        sf::Image placeholderImage;
        placeholderImage.create(64, 16, sf::Color::Transparent);
        for (int i = 0; i < 4; i++) { // 4 animation frames
            for (int x = 0; x < 16; x++) {
                for (int y = 0; y < 16; y++) {
                    if ((x-8)*(x-8) + (y-8)*(y-8) < 36) { // Circle shape
                        placeholderImage.setPixel(i*16 + x, y, sf::Color::Yellow);
                    }
                }
            }
        }
        sf::Texture placeholder;
        placeholder.loadFromImage(placeholderImage);
        mTextures["coin"] = placeholder;
    }
    
    // Load mushroom texture
    sf::Texture mushroomTexture;
    if (mushroomTexture.loadFromFile("resources/mushroom.png")) {
        mTextures["mushroom"] = mushroomTexture;
        std::cout << "Successfully loaded mushroom.png" << std::endl;
    }
    else {
        std::cerr << "Failed to load mushroom.png - creating placeholder texture" << std::endl;
        // Create a placeholder texture for mushroom
        sf::Image placeholderImage;
        placeholderImage.create(16, 16, sf::Color::Transparent);
        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                if (y >= 8) {
                    placeholderImage.setPixel(x, y, sf::Color::White);
                } else if ((x-8)*(x-8) + (y-4)*(y-4) < 25) {
                    placeholderImage.setPixel(x, y, sf::Color::Red);
                }
            }
        }
        sf::Texture placeholder;
        placeholder.loadFromImage(placeholderImage);
        mTextures["mushroom"] = placeholder;
    }
    
    // Load background texture
    sf::Texture backgroundTexture;
    if (backgroundTexture.loadFromFile("resources/background.png")) {
        mTextures["background"] = backgroundTexture;
        std::cout << "Successfully loaded background.png" << std::endl;
    }
    else {
        std::cerr << "Failed to load background.png - creating placeholder texture" << std::endl;
        // Create a placeholder texture for background
        sf::Image placeholderImage;
        placeholderImage.create(800, 600, sf::Color(107, 140, 255)); // Sky blue
        sf::Texture placeholder;
        placeholder.loadFromImage(placeholderImage);
        mTextures["background"] = placeholder;
    }
    
    // Load flag texture
    sf::Texture flagTexture;
    if (flagTexture.loadFromFile("resources/flag.png")) {
        mTextures["flag"] = flagTexture;
        std::cout << "Successfully loaded flag.png" << std::endl;
    }
    else {
        std::cerr << "Failed to load flag.png - creating placeholder texture" << std::endl;
        // Create a placeholder texture for flag
        sf::Image placeholderImage;
        placeholderImage.create(16, 32, sf::Color::Transparent);
        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 32; y++) {
                if (x < 2) {
                    placeholderImage.setPixel(x, y, sf::Color::White); // Pole
                } else if (y < 16) {
                    placeholderImage.setPixel(x, y, sf::Color::Green); // Flag
                }
            }
        }
        sf::Texture placeholder;
        placeholder.loadFromImage(placeholderImage);
        mTextures["flag"] = placeholder;
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
