#include <iostream>
#include "Game.h"
#include "Splash.h"
#include "Definitions.h"

Game::Game() {
    dt = FRAME_TIME;
    data->renderWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Xenon", sf::Style::Fullscreen);
    data->renderWindow.setMouseCursorVisible(false);
    if(!data->font.loadFromFile("media/PIXELADE.TTF"))
        std::cout << "error opening font\n";
    data->stateManager.addState(StateRef(new Splash(data)), true);

    accumulator = 0.f;
    currentTime = gameClock.getElapsedTime().asSeconds();

    while(data->renderWindow.isOpen()){
        data->stateManager.makeChanges();
        newTime = gameClock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        if(frameTime > FRAME_DELAY)
            frameTime = FRAME_DELAY;
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