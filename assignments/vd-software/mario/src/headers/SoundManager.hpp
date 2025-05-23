#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class SoundManager {
public:
    static SoundManager& getInstance();
    void loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
    void loadMusic(const std::string& name, const std::string& filename);
    void playMusic(const std::string& name, bool loop = true);
    void stopMusic(const std::string& name);

private:
    SoundManager(); // Private constructor for singleton
    ~SoundManager();
    
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
    std::map<std::string, sf::Music*> music;
};
