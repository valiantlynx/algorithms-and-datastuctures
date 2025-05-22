#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Block.hpp"
#include "Coin.hpp"
#include "Mushroom.hpp"
#include "Mario.hpp"

class Level {
public:
    explicit Level(const std::map<std::string, sf::Texture>& textures);
    
    void checkCollisions(Mario& mario);
    void render(sf::RenderWindow& window);
    
    bool isCompleted() const;

private:
    std::vector<std::unique_ptr<Block>> mBlocks;
    std::vector<std::unique_ptr<Coin>> mCoins;
    std::vector<std::unique_ptr<Mushroom>> mMushrooms;
    sf::Sprite mBackground;
    sf::Sprite mFlag;
    bool mLevelCompleted;
    
    // Store a reference to the textures map for later use
    const std::map<std::string, sf::Texture>& textures;
    
    void loadLevel(const std::map<std::string, sf::Texture>& textures);
    void createBlock(const sf::Texture& texture, BlockType type, float x, float y);
    void createCoin(const sf::Texture& texture, float x, float y);
    void createMushroom(const sf::Texture& texture, float x, float y);
    
    void checkBlockCollisions(Mario& mario);
    void checkCoinCollisions(Mario& mario);
    void checkMushroomCollisions(Mario& mario);
    void checkFlagCollision(Mario& mario);
};
