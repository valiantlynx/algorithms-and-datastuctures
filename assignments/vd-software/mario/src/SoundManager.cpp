#include "headers/SoundManager.hpp"
#include <iostream>

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager() {
    // it a Constructor
}

SoundManager::~SoundManager() {
    // Clean up the music resources
    for (auto& pair : music) {
        delete pair.second;
    }
}

void SoundManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Failed to load sound: " << filename << std::endl;
        return;
    }
    
    soundBuffers[name] = buffer;
    sounds[name] = sf::Sound(soundBuffers[name]);
}

void SoundManager::playSound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name].play();
    }
}

void SoundManager::loadMusic(const std::string& name, const std::string& filename) {
    sf::Music* newMusic = new sf::Music();
    if (!newMusic->openFromFile(filename)) {
        std::cerr << "Failed to load music: " << filename << std::endl;
        delete newMusic;
        return;
    }
    
    music[name] = newMusic;
}

void SoundManager::playMusic(const std::string& name, bool loop) {
    if (music.find(name) != music.end()) {
        music[name]->setLoop(loop);
        music[name]->play();
    }
}

void SoundManager::stopMusic(const std::string& name) {
    if (music.find(name) != music.end()) {
        music[name]->stop();
    }
}
