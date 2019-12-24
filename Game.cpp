#include <iostream>
#include "Game.h"
#include "Splash.h"

Game::Game() {
    data->renderWindow.create(sf::VideoMode(1280,800), "Xenon", sf::Style::Default);
    data->renderWindow.setMouseCursorVisible(false);
    if(!data->font.loadFromFile("media/PIXELADE.TTF"))
        std::cout << "error opening font\n";
    data->stateManager.addState(StateRef(new Splash(data)), true);
    run();
}

void Game::run() {
    float newTime, frameTime;
    float accumulator = 0.f;
    float currentTime = gameClock.getElapsedTime().asSeconds();

    while(data->renderWindow.isOpen()){
        data->stateManager.makeChanges();
        newTime = gameClock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        if(frameTime > 0.25f)
            frameTime = 0.25f;
        currentTime = newTime;
        accumulator += frameTime;
        while(accumulator >= dt){
            data->stateManager.getActiveState()->handleInput();
            data->stateManager.getActiveState()->update();
            accumulator -= dt;
        }
        data->stateManager.getActiveState()->draw();
    }
}
