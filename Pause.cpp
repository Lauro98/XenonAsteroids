#include <iostream>
#include "Pause.h"
#include "MainMenu.h"
#include "ToggableShield.h"
#include "Definitions.h"
#include "Settings.h"

Pause::Pause(GameDataRef dataRef): data(std::move(dataRef)){
}

void Pause::init() {
    data->soundManager.playPauseTheme();
    background.setTexture(data->textureManager.getTextureFromAtlas("pause"));
    for(int i=0; i<5; i++){
        text[i].setFont(data->font);
        text[i].setFillColor(sf::Color::White);
        text[i].setCharacterSize(60);
    }
    text[0].setPosition(50, (float)WINDOW_HEIGHT/4);
    text[1].setPosition(50, text[0].getPosition().y + 90); //power up
    text[2].setPosition(50,text[1].getPosition().y + 75); //power up
    text[3].setPosition(50, text[2].getPosition().y+100);
    text[4].setPosition(50, text[3].getPosition().y + 75);
    text[5].setPosition(50, text[4].getPosition().y + 75);

    text[0].setString("Resume");
    text[1].setString(BUY_TOGG_SHIELD_STRING);
    text[2].setString(BUY_TIME_SHIELD_STRING);
    text[3].setString("Settings");
    text[4].setString("Go to Main Menu");
    text[0].setFillColor(sf::Color::Red);
    selectedItemIndex = 0;
}

void Pause::handleInput() {
    sf::Event event{};
    while(data->renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed)
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    moveUp();
                    break;
                case sf::Keyboard::Down:
                    moveDown();
                    break;
                case sf::Keyboard::Space:
                        switch (selectedItemIndex) {
                            case 0:
                                data->soundManager.playResumeSound();
                                data->stateManager.popState();
                                break;
                            case 1:
                                if(data->panel.getScore() >= TOGGABLE_SHIELD_COST) {
                                    data->soundManager.playSelectionSound();
                                    if(data->spaceship.getDefenceStrategy()->getType() != toggableShield) {
                                        data->spaceship.setDefenceStrategy(toggableShield);
                                        data->panel.addPoints(-TOGGABLE_SHIELD_COST);
                                        break;
                                    }
                                    else {
                                        data->spaceship.getDefenceStrategy()->addShield();
                                        data->panel.addPoints(-TOGGABLE_SHIELD_COST);
                                        break;
                                    }
                                }
                                else
                                    data->soundManager.playDeniedSound();
                                break;
                            case 2:
                                if(data->panel.getScore() >= TIME_SHIELD_COST) {
                                    data->soundManager.playSelectionSound();
                                    if(data->spaceship.getDefenceStrategy()->getType() != timeShield) {
                                        data->spaceship.setDefenceStrategy(timeShield);
                                        data->panel.addPoints(-TIME_SHIELD_COST);
                                    }
                                    else {
                                        data->spaceship.getDefenceStrategy()->addShield();
                                        data->panel.addPoints(-TIME_SHIELD_COST);
                                    }
                                }
                                else
                                    data->soundManager.playDeniedSound();
                                break;
                            case 3:
                                data->soundManager.playSelectionSound();
                                data->stateManager.addState(StateRef(new Settings(data)), false);
                                break;
                            case 4:
                                data->soundManager.playSelectionSound();
                                data->stateManager.addState(StateRef(new MainMenu(data)), true);
                                break;
                        }
                default:
                    continue;
            }
    }
}

void Pause::update() {
    data->panel.setShieldText(data->spaceship.getDefenceStrategy()->getShieldLife());
    if(data->spaceship.getDefenceStrategy()->getType() == toggableShield)
        text[1].setString(ADD_TOGG_SHIELD_STRING);
    else
        text[1].setString(BUY_TOGG_SHIELD_STRING);
    if(data->spaceship.getDefenceStrategy()->getType() == timeShield)
        text[2].setString(ADD_TIME_SHIELD_STRING);
    else
        text[2].setString(BUY_TIME_SHIELD_STRING);
}

void Pause::draw() {
    data->renderWindow.clear();
    data->renderWindow.draw(background);
    data->panel.draw(data->renderWindow);
    for(int i = 0; i<5; i++)
        data->renderWindow.draw(text[i]);
    data->renderWindow.display();
}

void Pause::moveUp() {
    if(selectedItemIndex - 1 >= 0){
        text[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
        data->soundManager.playNavigationSound();
    }
}

void Pause::moveDown() {
    if(selectedItemIndex + 1 < 5){
        text[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
        data->soundManager.playNavigationSound();
    }
}