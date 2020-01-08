#include "SoundManager.h"
#include "Definitions.h"

SoundManager::SoundManager() {
    loadSound("boost", "media/boost.wav");
    loadSound("denied", "media/negative.wav");
    loadSound("explosion", "media/Explosion+8.wav");
    loadSound("gameover", "media/gameover.wav");
    loadSound("navigation", "media/click.wav");
    loadSound("pause", "media/misc_menu_2.wav");
    loadSound("resume", "media/sharp_echo.wav");
    loadSound("selection", "media/beep.wav");
    loadSound("shield", "media/shield.wav");
    loadSound("shoot", "media/ammo.wav");
    gameTheme.openFromFile("media/come_together.wav");
    gameTheme.setLoop(true);
    mainTheme.openFromFile("media/HansZimmer-Interstellar.wav");
    mainTheme.setLoop(true);
    mainTheme.setAttenuation(3);
    pauseTheme.openFromFile("media/come_together_piano.wav");
    pauseTheme.setLoop(true);
    fxVolume = DEFAULT_FX_VOLUME;
    musicVolume = DEFAULT_MUSIC_VOLUME;
    for (const auto &i : soundAtlas)
        soundAtlas[i.first].setVolume((float) fxVolume);
    mainTheme.setVolume((float)musicVolume);
    gameTheme.setVolume((float)musicVolume);
    pauseTheme.setVolume((float)musicVolume);
}

void SoundManager::loadSound(const std::string &name, const std::string &filePath) {
    soundBufferAtlas[name].loadFromFile(filePath);
    soundAtlas[name].setBuffer(soundBufferAtlas[name]);
}

void SoundManager::playNavigationSound() {
    soundAtlas["navigation"].play();
}

void SoundManager::playSelectionSound() {
    soundAtlas["selection"].play();
}

void SoundManager::playDeniedSound() {
    soundAtlas["denied"].play();
}

void SoundManager::playResumeSound() {
    pauseTheme.stop();
    gameTheme.play();
    soundAtlas["resume"].play();
}

void SoundManager::playBoostSound() {
    if(soundAtlas["boost"].getStatus() != sf::Sound::Playing)
        soundAtlas["boost"].play();
}

void SoundManager::pauseBoostSound() {
    soundAtlas["boost"].pause();
}

void SoundManager::playExplosionSound() {
    soundAtlas["explosion"].play();
}

void SoundManager::playShieldSound() {
    soundAtlas["shield"].play();
}

void SoundManager::playShootSound() {
    soundAtlas["shoot"].play();
}

void SoundManager::playGameTheme() {
    pauseTheme.stop();
    mainTheme.stop();
    if(gameTheme.getStatus() != sf::Music::Status::Playing)
        gameTheme.play();
}

void SoundManager::playGameOverSound() {
    pauseTheme.stop();
    gameTheme.stop();
    soundAtlas["gameover"].play();
    mainTheme.play();
}

void SoundManager::playMainTheme() {
    gameTheme.stop();
    pauseTheme.stop();
    if(mainTheme.getStatus() != sf::Music::Status::Playing)
        mainTheme.play();
}

void SoundManager::playPauseTheme() {
    gameTheme.pause();
    soundAtlas["pause"].play();
    pauseTheme.play();
}

void SoundManager::fxVolumeUp() {
    if(fxVolume+1<=100) {
        playNavigationSound();
        fxVolume++;
        for (const auto &i : soundAtlas)
            soundAtlas[i.first].setVolume((float) fxVolume);
    }
    else
        playDeniedSound();
}

void SoundManager::fxVolumeDown() {
    if(fxVolume-1>=0) {
        playNavigationSound();
        fxVolume--;
        for (const auto &i : soundAtlas)
            soundAtlas[i.first].setVolume((float) fxVolume);
    }
    else
        playDeniedSound();
}

void SoundManager::musicVolumeUp() {
    if(musicVolume+1<=100) {
        playNavigationSound();
        musicVolume++;
        mainTheme.setVolume((float)musicVolume);
        gameTheme.setVolume((float)musicVolume);
        pauseTheme.setVolume((float)musicVolume);
    }
    else
        playDeniedSound();
}

void SoundManager::musicVolumeDown() {
    if(musicVolume-1>=0) {
        playNavigationSound();
        musicVolume--;
        mainTheme.setVolume((float)musicVolume);
        gameTheme.setVolume((float)musicVolume);
        pauseTheme.setVolume((float)musicVolume);
    }
    else
        playDeniedSound();
}

unsigned int SoundManager::getMusicVolume() {
    return musicVolume;
}

unsigned int SoundManager::getFxVolume() {
    return fxVolume;
}
