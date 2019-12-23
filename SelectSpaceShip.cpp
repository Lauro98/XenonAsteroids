#include "SelectSpaceShip.h"
#include "Spaceship.h"
#include "GameLoop.h"

#include <utility>
#include <iostream>

SelectSpaceShip::SelectSpaceShip(GameDataRef dataRef) : data(std::move(dataRef)) {
}

void SelectSpaceShip::init() {

    background.setTexture(data->textureManager.getTextureFromAtlas("menu"));
    ship[0].setTexture(data->textureManager.getTextureFromAtlas("lennon"));
    ship[0].setTextureRect(sf::IntRect(0,0,58,79));
    ship[0].setPosition((float)sf::VideoMode::getDesktopMode().width/5*1, (float)sf::VideoMode::getDesktopMode().height/3);
    ship[1].setTexture(data->textureManager.getTextureFromAtlas("macca"));
    ship[1].setTextureRect(sf::IntRect(0,0,36,66));
    ship[1].setPosition((float)sf::VideoMode::getDesktopMode().width/5*2, (float)sf::VideoMode::getDesktopMode().height/3);
    ship[2].setTexture(data->textureManager.getTextureFromAtlas("harrison"));
    ship[2].setTextureRect(sf::IntRect(0,0,52,66));
    ship[2].setPosition((float)sf::VideoMode::getDesktopMode().width/5*3, (float)sf::VideoMode::getDesktopMode().height/3);
    ship[3].setTexture(data->textureManager.getTextureFromAtlas("starr"));
    ship[3].setTextureRect(sf::IntRect(0,0,32,44));
    ship[3].setPosition((float)sf::VideoMode::getDesktopMode().width/5*4, (float)sf::VideoMode::getDesktopMode().height/3);
    for(int i=0; i<4; i++) {
        name[i].setFont(data->font);
        name[i].setCharacterSize(40);
        name[i].setFillColor(sf::Color::White);
        name[i].setPosition(ship[i].getPosition().x, ship[i].getPosition().y+100);
        ship[i].setOrigin(ship[i].getLocalBounds().width / 2,ship[i].getLocalBounds().height / 2);
    }
    name[0].setFillColor(sf::Color::Red);
    name[0].setString("Lennon");
    name[1].setString("Macca");
    name[2].setString("Harrison");
    name[3].setString("Starr");
    selectedItemIndex = 0;
}

void SelectSpaceShip::handleInput() {
    sf::Event event{};
    while(data->renderWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed)
            data->renderWindow.close();
        if(event.type == sf::Event::KeyPressed)
            switch (event.key.code){
                case sf::Keyboard::Left:
                    moveLeft();
                    break;
                case sf::Keyboard::Right:
                    moveRight();
                    break;
                case sf::Keyboard::Space:
                    switch (selectedItemIndex){
                        case 0:
                            data->spaceship = {data->textureManager, lennon};
                            data->stateManager.addState(StateRef(new GameLoop(data)), true);
                            break;
                        case 1:
                            data->spaceship = {data->textureManager, macca};
                            data->stateManager.addState(StateRef(new GameLoop(data)), true);
                            break;
                        case 2:
                            data->spaceship = {data->textureManager, harrison};
                            data->stateManager.addState(StateRef(new GameLoop(data)), true);
                            break;
                        case 3:
                            data->spaceship = {data->textureManager, starr};
                            data->stateManager.addState(StateRef(new GameLoop(data)), true);
                            break;
                    }
                default:
                    continue;
            }
    }
}

void SelectSpaceShip::moveLeft() {
    if(selectedItemIndex - 1 >= 0){
        name[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        name[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void SelectSpaceShip::moveRight() {
    if(selectedItemIndex + 1 < 4){
        name[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        name[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void SelectSpaceShip::update() {
    for(int i=0; i<4; i++){
        if(i != selectedItemIndex)
            ship[i].setRotation(0);
    }
    ship[selectedItemIndex].rotate(0.5);
}

void SelectSpaceShip::draw() {
    data->renderWindow.clear();
    data->renderWindow.draw(background);
    for(int i = 0; i<4; i++) {
        data->renderWindow.draw(name[i]);
        data->renderWindow.draw(ship[i]);
    }
    data->renderWindow.display();
}
