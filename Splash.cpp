#include "Splash.h"
#include "MainMenu.h"
#include <iostream>
#include <utility>

void Splash::init() {
   background.setTexture(data->textureManager.getTextureFromAtlas("splash"));
}

void Splash::handleInput() {
    sf::Event event{};
    while(data->renderWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed)
            data->renderWindow.close();
    }
}

void Splash::update() {
    if(clock.getElapsedTime().asSeconds() > 3.f){
        data->stateManager.addState(StateRef(new MainMenu(data)), true);
    }
}

void Splash::draw() {
    data->renderWindow.clear();
    data->renderWindow.draw(background);
    data->renderWindow.display();
}

Splash::Splash(GameDataRef dataRef) : data (std::move(dataRef)) {
}
