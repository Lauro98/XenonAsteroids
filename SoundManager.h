#ifndef XENON_SOUNDMANAGER_H
#define XENON_SOUNDMANAGER_H
#include <map>
#include "SFML/Audio.hpp"

class SoundManager {
public:
    SoundManager();
    void playNavigationSound();
    void playSelectionSound();
    void playDeniedSound();
    void playResumeSound();
    void playBoostSound();
    void pauseBoostSound();
    void playExplosionSound();
    void playShieldSound();
    void playShootSound();
    void playGameOverSound();
    void playGameTheme();
    void playMainTheme();
    void playPauseTheme();
    void fxVolumeUp();
    void fxVolumeDown();
    void musicVolumeUp();
    void musicVolumeDown();
    unsigned int getFxVolume();
    unsigned int getMusicVolume();
private:
    std::map<std::string, sf::Sound> soundAtlas;
    std::map<std::string, sf::SoundBuffer> soundBufferAtlas;
    sf::Music gameTheme;
    sf::Music mainTheme;
    sf::Music pauseTheme;
    unsigned int fxVolume;
    unsigned int musicVolume;
    void loadSound(const std::string &name, const std::string &filePath);
};

#endif