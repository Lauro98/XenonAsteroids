#include "Settings.h"
#include "Definitions.h"

Settings::Settings(GameDataRef dataRef): data(std::move(dataRef)) { }

void Settings::init() {
    background.setTexture(data->textureManager.getTextureFromAtlas("settings"));
    for(int i=0; i<4; i++){
        text[i].setFont(data->font);
        text[i].setFillColor(sf::Color::White);
        text[i].setCharacterSize(62);
    }
    text[0].setPosition(FIRST_VOLUME_BOX_AXIS, FIRST_VOLUME_BOX_ORD);
    text[1].setPosition(FIRST_VOLUME_BOX_AXIS, text[0].getPosition().y + VOLUME_BOX_GAP);
    text[2].setPosition(74, text[1].getPosition().y + VOLUME_BOX_GAP*2);
    text[3].setPosition(74, text[2].getPosition().y + VOLUME_BOX_GAP*2);
    text[0].setString(std::to_string(data->soundManager.getMusicVolume()));
    text[1].setString(std::to_string(data->soundManager.getFxVolume()));
    text[2].setString("View Commands");
    text[3].setString("Done");
    text[0].setFillColor(sf::Color::Red);
    selectedItemIndex = 0;
    viewingCommands = false;
}

void Settings::moveUp() {
    if(selectedItemIndex - 1 >= 0){
        text[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
        data->soundManager.playNavigationSound();
    }
}

void Settings::moveDown() {
    if(selectedItemIndex + 1 < 4){
        text[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
        data->soundManager.playNavigationSound();
    }
}

void Settings::handleInput() {
    sf::Event event{};
    while(data->renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed)
            switch (event.key.code) {
                case sf::Keyboard::Left:
                    if(selectedItemIndex == 0)
                        data->soundManager.musicVolumeDown();
                    if(selectedItemIndex == 1)
                        data->soundManager.fxVolumeDown();
                    break;
                case sf::Keyboard::Right:
                    if(selectedItemIndex == 0)
                        data->soundManager.musicVolumeUp();
                    if(selectedItemIndex == 1)
                        data->soundManager.fxVolumeUp();
                    break;
                case sf::Keyboard::Up:
                    moveUp();
                    break;
                case sf::Keyboard::Down:
                    moveDown();
                    break;
                case sf::Keyboard::Space:
                    if(!viewingCommands) {
                        switch (selectedItemIndex) {
                            case 0:
                                break;
                            case 1:
                                break;
                            case 2:
                                data->soundManager.playSelectionSound();
                                viewingCommands = true;
                                break;
                            case 3:
                                data->soundManager.playSelectionSound();
                                data->stateManager.popState();
                                break;
                        }
                    }
                    else
                        viewingCommands = false;
                default:
                    continue;
            }
    }
}

void Settings::update() {
    if(viewingCommands)
        background.setTexture(data->textureManager.getTextureFromAtlas("commands"));
    else
        background.setTexture(data->textureManager.getTextureFromAtlas("settings"));
    text[0].setString(std::to_string(data->soundManager.getMusicVolume()));
    text[1].setString(std::to_string(data->soundManager.getFxVolume()));
}

void Settings::draw() {
    data->renderWindow.clear();
    data->renderWindow.draw(background);
    if(!viewingCommands) {
        for(int i = 0; i < 4; i++)
            data->renderWindow.draw(text[i]);
    }
    data->renderWindow.display();
}