#include "Level.hpp"
#include <iostream>

Level::Level(const std::map<std::string, sf::Texture>& textures)
    : mLevelCompleted(false)
    , textures(textures)  // Initialize the textures reference
{
    loadLevel(textures);
}

void Level::checkCollisions(Mario& mario) {
    // Apply gravity first
    mario.applyGravity(0.016f); // Approximately 1/60 seconds
    
    // Check collisions
    checkBlockCollisions(mario);
    checkCoinCollisions(mario);
    checkMushroomCollisions(mario);
    checkFlagCollision(mario);
    
    // Update mushrooms
    for (auto& mushroom : mMushrooms) {
        mushroom->update(0.016f);
    }
    
    // Update coins
    for (auto& coin : mCoins) {
        coin->update(0.016f);
    }
    
    // Update blocks
    for (auto& block : mBlocks) {
        block->update(0.016f);
    }
}

void Level::render(sf::RenderWindow& window) {
    // Draw background
    window.draw(mBackground);
    
    // Draw blocks
    for (const auto& block : mBlocks) {
        block->render(window);
    }
    
    // Draw coins
    for (const auto& coin : mCoins) {
        coin->render(window);
    }
    
    // Draw mushrooms
    for (const auto& mushroom : mMushrooms) {
        mushroom->render(window);
    }
    
    // Draw flag
    window.draw(mFlag);
}

bool Level::isCompleted() const {
    return mLevelCompleted;
}

void Level::loadLevel(const std::map<std::string, sf::Texture>& textures) {
    // Load textures
    sf::Texture blockTexture;
    sf::Texture coinTexture;
    sf::Texture mushroomTexture;
    
    if (textures.find("blocks") != textures.end()) {
        blockTexture = textures.at("blocks");
    }
    
    if (textures.find("coin") != textures.end()) {
        coinTexture = textures.at("coin");
    }
    
    if (textures.find("mushroom") != textures.end()) {
        mushroomTexture = textures.at("mushroom");
    }
    
    // Create ground
    for (int i = 0; i < 50; ++i) {
        createBlock(blockTexture, BlockType::Solid, i * 16.f, 500.f);
    }
    
    // Create platforms
    createBlock(blockTexture, BlockType::Solid, 200.f, 400.f);
    createBlock(blockTexture, BlockType::Solid, 216.f, 400.f);
    createBlock(blockTexture, BlockType::Solid, 232.f, 400.f);
    
    // Create question blocks with coins
    createBlock(blockTexture, BlockType::Question, 150.f, 350.f);
    createBlock(blockTexture, BlockType::Question, 300.f, 350.f);
    createBlock(blockTexture, BlockType::Question, 350.f, 350.f);
    
    // Create brick blocks
    createBlock(blockTexture, BlockType::Brick, 200.f, 350.f);
    createBlock(blockTexture, BlockType::Brick, 250.f, 350.f);
    
    // Create coins
    createCoin(coinTexture, 150.f, 450.f);
    createCoin(coinTexture, 170.f, 450.f);
    createCoin(coinTexture, 190.f, 450.f);
    createCoin(coinTexture, 400.f, 450.f);
    createCoin(coinTexture, 420.f, 450.f);
    
    // Set up background
    if (textures.find("background") != textures.end()) {
        mBackground.setTexture(textures.at("background"));
        mBackground.setScale(
            800.f / mBackground.getTextureRect().width,
            600.f / mBackground.getTextureRect().height
        );
    }
    
    // Set up flag
    if (textures.find("flag") != textures.end()) {
        mFlag.setTexture(textures.at("flag"));
        mFlag.setPosition(700.f, 400.f);
    }
}

void Level::createBlock(const sf::Texture& texture, BlockType type, float x, float y) {
    auto block = std::make_unique<Block>(texture, type);
    block->setPosition(x, y);
    mBlocks.push_back(std::move(block));
}

void Level::createCoin(const sf::Texture& texture, float x, float y) {
    auto coin = std::make_unique<Coin>(texture);
    coin->setPosition(x, y);
    mCoins.push_back(std::move(coin));
}

void Level::createMushroom(const sf::Texture& texture, float x, float y) {
    auto mushroom = std::make_unique<Mushroom>(texture);
    mushroom->setPosition(x, y);
    mMushrooms.push_back(std::move(mushroom));
}

void Level::checkBlockCollisions(Mario& mario) {
    bool onGround = false;
    sf::FloatRect marioBounds = mario.getBounds();
    sf::Vector2f marioPosition = mario.getPosition();
    
    for (auto& block : mBlocks) {
        sf::FloatRect blockBounds = block->getBounds();
        
        // Check if Mario hits block from below
        if (marioPosition.y < blockBounds.top + blockBounds.height &&
            marioPosition.y > blockBounds.top &&
            marioBounds.left + marioBounds.width > blockBounds.left &&
            marioBounds.left < blockBounds.left + blockBounds.width) {
            
            // Mario hits block from below
            block->hit(
                [&]() {
                    // Handle brick block destruction
                    // In a real implementation, you'd mark the block for removal
                },
                [&]() {
                    // Release power-up or coin
                    if (block->hasItem()) {
                        // 50% chance for mushroom, 50% for coin
                        if (rand() % 2 == 0) {
                            // Fix: Pass the texture from textures map instead of float height
                            if (!mMushrooms.empty() && textures.find("mushroom") != textures.end()) {
                                createMushroom(textures.at("mushroom"), blockBounds.left, blockBounds.top - 16.f);
                            }
                        }
                        else {
                            // Fix: Pass the texture from textures map instead of float height
                            if (!mCoins.empty() && textures.find("coin") != textures.end()) {
                                createCoin(textures.at("coin"), blockBounds.left, blockBounds.top - 16.f);
                            }
                        }
                    }
                }
            );
            
            // Stop Mario's upward movement
            mario.setPosition(marioPosition.x, blockBounds.top + blockBounds.height);
        }
        
        // Check if Mario lands on top of block
        if (marioPosition.y + marioBounds.height >= blockBounds.top &&
            marioPosition.y + marioBounds.height <= blockBounds.top + 10.f &&
            marioBounds.left + marioBounds.width > blockBounds.left &&
            marioBounds.left < blockBounds.left + blockBounds.width) {
            
            // Mario lands on block
            mario.setPosition(marioPosition.x, blockBounds.top - marioBounds.height);
            onGround = true;
        }
        
        // Check horizontal collisions
        if (marioPosition.y + marioBounds.height > blockBounds.top &&
            marioPosition.y < blockBounds.top + blockBounds.height) {
            
            // Mario hits block from left
            if (marioPosition.x + marioBounds.width >= blockBounds.left &&
                marioPosition.x + marioBounds.width <= blockBounds.left + 5.f) {
                mario.setPosition(blockBounds.left - marioBounds.width, marioPosition.y);
            }
            
            // Mario hits block from right
            if (marioPosition.x <= blockBounds.left + blockBounds.width &&
                marioPosition.x >= blockBounds.left + blockBounds.width - 5.f) {
                mario.setPosition(blockBounds.left + blockBounds.width, marioPosition.y);
            }
        }
    }
    
    mario.setOnGround(onGround);
}

void Level::checkCoinCollisions(Mario& mario) {
    sf::FloatRect marioBounds = mario.getBounds();
    
    for (auto& coin : mCoins) {
        if (!coin->isCollected() && marioBounds.intersects(coin->getBounds())) {
            coin->collect();
            mario.incrementScore(Coin::COIN_VALUE);
        }
    }
}

void Level::checkMushroomCollisions(Mario& mario) {
    sf::FloatRect marioBounds = mario.getBounds();
    
    for (auto& mushroom : mMushrooms) {
        if (!mushroom->isCollected() && marioBounds.intersects(mushroom->getBounds())) {
            mushroom->collect();
            mario.setState(MarioState::Big);
        }
    }
}

void Level::checkFlagCollision(Mario& mario) {
    if (mario.getBounds().intersects(mFlag.getGlobalBounds())) {
        mLevelCompleted = true;
    }
}
