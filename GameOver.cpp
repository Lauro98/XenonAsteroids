#include <iostream>
#include "GameOver.h"
#include "SelectSpaceShip.h"
#include "MainMenu.h"
#include "Definitions.h"

GameOver::GameOver(GameDataRef dataRef): data(std::move(dataRef)){
}

void GameOver::init() {
    background.setTexture(data->textureManager.getTextureFromAtlas("game_over"));
    if(!font.loadFromFile("media/PIXELADE.TTF"))
        std::cout << "error opening font\n";
    for(int i=0; i<2; i++){
        text[i].setFont(font);
        text[i].setFillColor(sf::Color::Black);
        text[i].setCharacterSize(70);
        float j = i + 1;
        text[i].setPosition(300, WINDOW_HEIGHT/(j+1)*j);
    }
    text[0].setString("Play Again");
    text[1].setString("Return to Main Menu");
    text[0].setFillColor(sf::Color::Red);
    selectedItemIndex = 0;

}

void GameOver::handleInput() {
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
                            data->stateManager.addState(StateRef(new MainMenu(data)), true);
                            break;
                    }
                default:
                    continue;
            }
    }
}

void GameOver::update() {

}

void GameOver::draw() {
    data->renderWindow.clear();
    data->renderWindow.draw(background);
    for(int i = 0; i<2; i++)
        data->renderWindow.draw(text[i]);
    data->renderWindow.display();
}

void GameOver::moveUp() {
    if(selectedItemIndex - 1 >= 0){
        text[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex--;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
    }

}

void GameOver::moveDown() {
    if(selectedItemIndex + 1 < 2){
        text[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex++;
        text[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}