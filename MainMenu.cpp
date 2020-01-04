#include "MainMenu.h"
#include "SelectSpaceShip.h"
#include "Definitions.h"
#include <utility>
#include <iostream>

MainMenu::MainMenu(GameDataRef dataRef): data(std::move(dataRef)){
}

void MainMenu::init() {
    background.setTexture(data->textureManager.getTextureFromAtlas("menu"));
    for(int i=0; i<3; i++){
        text[i].setFont(data->font);
        text[i].setFillColor(sf::Color::White);
        text[i].setCharacterSize(70);
        float j = i + 1;
        text[i].setPosition(50, (float)WINDOW_HEIGHT/(j+1)*j);
    }
    text[0].setString("Play");
    text[1].setString("Settings");
    text[2].setString("Exit Game");
    text[0].setFillColor(sf::Color::Red);
    selectedItemIndex = 0;

}

void MainMenu::handleInput() {
    sf::Event event{};
    while(data->renderWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed)
            data->renderWindow.close();
        if(event.type == sf::Event::KeyPressed)
            switch (event.key.code){
            case sf::Keyboard::Up:
                moveUp();
                break;
            case sf::Keyboard::Down:
                moveDown();
                break;
            case sf::Keyboard::Space:
                switch (selectedItemIndex){
                    case 0:
                        data->stateManager.addState(StateRef(new SelectSpaceShip(data)), true);
                        break;
                    case 1:
                        std::cout << "pressed settings\n";
                        break;
                    case 2:
                        data->renderWindow.close();
                        break;
                }
                default:
                    continue;
        }
    }
}

void MainMenu::update() {

}

void MainMenu::draw() {
    data->renderWindow.clear();
    data->renderWindow.draw(background);
    for(int i = 0; i<3; i++)
        data->renderWindow.draw(text[i]);
    data->renderWindow.display();
}

void MainMenu::moveUp() {
    if(selectedItemIndex - 1 >= 0){
        text[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
    }

}

void MainMenu::moveDown() {
    if(selectedItemIndex + 1 < 3){
        text[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
