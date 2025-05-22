#include "Game.hpp"
#include <iostream>
#include <exception>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
    try {
        // Set VideoMode explicitly for better hardware compatibility
        sf::VideoMode videoMode(800, 600);
        if (!videoMode.isValid()) {
            std::cerr << "Error: Video mode is not valid!" << std::endl;
            videoMode = sf::VideoMode(800, 600, 32); // Try with explicit bit depth
        }
        
        // Create standalone window first to test SFML setup
        sf::RenderWindow testWindow;
        testWindow.create(videoMode, "SFML Test Window");
        if (!testWindow.isOpen()) {
            std::cerr << "Error: Failed to create test window!" << std::endl;
        } else {
            std::cout << "SFML test window created successfully." << std::endl;
            testWindow.close();
        }
        
        // Initialize and run game
        Game game;
        game.run();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
