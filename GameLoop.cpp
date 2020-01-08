#include "GameLoop.h"
#include "Definitions.h"
#include <utility>
#include <iostream>
#include "Asteroid.h"
#include "GameOver.h"
#include "Pause.h"

GameLoop::GameLoop(GameDataRef dataRef) {
    data = std::move(dataRef);
    data->panel = {data->font, data->textureManager};
    gameOver = false;
    data->soundManager.playGameTheme();
}

GameLoop::~GameLoop() {
    int n = entities.size();
    for (int i = 0; i < n; i++)
        delete(entities.at(i));
}

void GameLoop::init() {
    for (int i = 0; i < INITIAL_ASTEROIDS; i++) {
        entities.emplace_back(new Asteroid(data->textureManager));
    }
    background.setTexture(data->textureManager.getTextureFromAtlas("background"));
    background.setOrigin(0,0);
}

void GameLoop::handleInput() {
    sf::Event event{};
    while (data->renderWindow.pollEvent(event)) {
        if (event.type == sf::Event::EventType::Closed)
            data->renderWindow.close();
        if(event.type == sf::Event::KeyPressed && !gameOver){
            if(event.key.code == sf::Keyboard::S) {
                if(data->spaceship.getDefenceStrategy()->getType() == none)
                    data->soundManager.playDeniedSound();
                else
                    data->soundManager.playShieldSound();
                data->spaceship.getDefenceStrategy()->activateShield();
            }
        }
    }
    if (!gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            data->spaceship.turnLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            data->spaceship.turnRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            data->soundManager.playBoostSound();
            data->spaceship.setBoosting(true);
            data->spaceship.update();
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            data->soundManager.pauseBoostSound();
            data->spaceship.setBoosting(false);
            data->spaceship.update();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            data->spaceship.shoot();
            if(data->spaceship.isShooting())
                data->soundManager.playShootSound();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            data->stateManager.addState(StateRef(new Pause(data)), false);
        }
    }
}

void GameLoop::update() {
    data->panel.setShieldText(data->spaceship.getDefenceStrategy()->getShieldLife());
    for (int i = 0; i < entities.size(); i++) {
        entities.at(i)->update();
        if (!entities.at(i)->isAlive()) {
            entities.erase(entities.begin() + i);
        }
    }
    if(!gameOver){
        if (asteroidsGen.getElapsedTime().asSeconds() >= ASTEROID_GEN_TIME) {
            entities.emplace_back(new Asteroid(data->textureManager));
            data->panel.addPoints(POINT_BONUS);
            asteroidsGen.restart();
        }
        if (data->spaceship.isShooting()) {
            entities.emplace_back(new Projectile(data->textureManager, data->spaceship));
            data->panel.addPoints(POINT_MALUS);
        }
        for (int i = 0; i < entities.size(); i++) {
            for (int j = 0; j < entities.size(); j++) {
                if (entities.at(i)->getType() == EntityType::projectile &&
                    entities.at(j)->getType() == EntityType::asteroid) {
                    if (Collision::PixelPerfectTest(entities.at(i)->getSprite(), entities.at(j)->getSprite())) {
                        entities.emplace_back(new Explosion(data->textureManager, *entities.at(j)));
                        entities.emplace_back(new Asteroid(data->textureManager, *entities.at(j)));
                        entities.emplace_back(new Asteroid(data->textureManager, *entities.at(j)));
                        data->soundManager.playExplosionSound();
                        entities.at(i)->terminate();
                        entities.at(j)->terminate();
                        data->panel.addPoints(ASTEROID_EXPL);
                    }
                }
                if (entities.at(i)->getType() == EntityType::projectile &&
                    entities.at(j)->getType() == EntityType::rubble) {
                    if (Collision::PixelPerfectTest(entities.at(i)->getSprite(), entities.at(j)->getSprite())) {
                        entities.emplace_back(new Explosion(data->textureManager, *entities.at(j)));
                        data->soundManager.playExplosionSound();
                        entities.at(i)->terminate();
                        entities.at(j)->terminate();
                        data->panel.addPoints(RUBBLE_EXPL);
                    }
                }
            }
        }
        for (int i = 0; i < entities.size(); i++) {
            if (data->spaceship.getDefenceStrategy()->getType() == none ||
                (data->spaceship.getDefenceStrategy()->getType() != none
                 && !data->spaceship.getDefenceStrategy()->isVisible())) {
                if (entities.at(i)->getType() == EntityType::asteroid ||
                    entities.at(i)->getType() == EntityType::rubble) {
                    if (Collision::PixelPerfectTest(entities.at(i)->getSprite(), data->spaceship.getSprite()) ||
                        Collision::PixelPerfectTest(entities.at(i)->getSprite(),
                                                    data->spaceship.getDefenceStrategy()->getShieldSprite())) {
                        data->soundManager.pauseBoostSound();
                        data->soundManager.playExplosionSound();
                        entities.emplace_back(new Explosion(data->textureManager, data->spaceship));
                        gameOver = true;
                    }
                }
            }
            if (data->spaceship.getDefenceStrategy()->getType() != none &&
                data->spaceship.getDefenceStrategy()->isVisible() &&
                entities.at(i)->getType() != EntityType::projectile) {
                if (Collision::PixelPerfectTest(entities.at(i)->getSprite(),
                                                data->spaceship.getDefenceStrategy()->getShieldSprite())) {
                    if (entities.at(i)->getType() == EntityType::asteroid) {
                        entities.emplace_back(new Asteroid(data->textureManager, *entities.at(i)));
                        entities.emplace_back(new Asteroid(data->textureManager, *entities.at(i)));
                    }
                    entities.emplace_back(new Explosion(data->textureManager, *entities.at(i)));
                    data->soundManager.playExplosionSound();
                    entities.at(i)->terminate();
                    data->panel.addPoints(POINT_MALUS);
                    data->spaceship.getDefenceStrategy()->impact();
                }
            }
        }
    }
    if (gameOver && entities.at(entities.size()-1)->getAnimation().isAnimEnded()) {
        data->stateManager.addState(StateRef(new GameOver(data)), true);
    }
}

void GameLoop::draw() {
    data->renderWindow.clear();
    data->renderWindow.draw(background);
    if(!gameOver)
        data->spaceship.draw(data->renderWindow);
    if(data->spaceship.getDefenceStrategy()->getType() != none && data->spaceship.getDefenceStrategy()->isVisible() && !gameOver)
        data->spaceship.getDefenceStrategy()->draw(data->spaceship.getSprite(), data->renderWindow);
    for(int i = 0; i < entities.size(); i++)
        if(entities.at(i)->isAlive())
            entities.at(i)->draw(data->renderWindow);
    data->panel.draw(data->renderWindow);
    data->renderWindow.display();
}