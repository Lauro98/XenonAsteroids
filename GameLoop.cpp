#include "GameLoop.h"

#include <utility>
#include <iostream>
#include "Asteroid.h"
#include "GameOver.h"
#include "Pause.h"

GameLoop::GameLoop(GameDataRef dataRef) {
    data = std::move(dataRef);
    data->panel = {data->font, data->textureManager};
    isGameOver = false;
}

GameLoop::~GameLoop() {
    int n = entities.size();
    for (int i = 0; i < n; i++)
        delete(entities.at(i));
}


void GameLoop::init() {
    for (int i = 0; i < 3; i++) {
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
        if(event.type == sf::Event::KeyPressed && !isGameOver){
            if(event.key.code == sf::Keyboard::S)
                data->spaceship.getDefenceStrategy()->activateShield();
        }

    }
    if (!isGameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            data->spaceship.turnLeft();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            data->spaceship.turnRight();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            data->spaceship.setBoosting(true);
            data->spaceship.updatePosition();
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            data->spaceship.setBoosting(false);
            data->spaceship.updatePosition();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            if (asteroidsGen.getElapsedTime().asSeconds() >= data->spaceship.getFireRate()) {
                data->spaceship.setShooting(true);
                asteroidsGen.restart();
            }
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            data->spaceship.setShooting(false);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
            data->stateManager.addState(StateRef(new Pause(data)), false);
        }
    }
}

void GameLoop::update() {
    if (asteroidsGen.getElapsedTime().asSeconds() >= 10 && !isGameOver) {
        entities.emplace_back(new Asteroid(data->textureManager));
        data->panel.addPoints(5);
        asteroidsGen.restart();
    }

    if (shootClock.getElapsedTime().asSeconds() >= data->spaceship.getFireRate() && data->spaceship.getShooting() &&
        !isGameOver) {
        shootClock.restart();
        entities.emplace_back(new Projectile(data->textureManager, data->spaceship));
        data->panel.addPoints(-2);
    }

    for (int i = 0; i < entities.size(); i++) {
        entities.at(i)->updatePosition();
        entities.at(i)->getAnimation().update(entities.at(i)->getSprite());
        if (!entities.at(i)->getHp()) {
            entities.erase(entities.begin() + i);
        }
    }

    data->spaceship.getDefenceStrategy()->update();
    data->panel.setShieldText(data->spaceship.getDefenceStrategy()->getShieldLife());

    if (!isGameOver) {
        for (int i = 0; i < entities.size(); i++) {
            for (int j = 0; j < entities.size(); j++) {
                if (entities.at(i)->getType() == EntityType::projectile &&
                    entities.at(j)->getType() == EntityType::asteroid) {
                    if (Collision::PixelPerfectTest(entities.at(i)->getSprite(), entities.at(j)->getSprite())) {
                        entities.emplace_back(new Explosion(data->textureManager, *entities.at(i)));
                        entities.emplace_back(new Asteroid(data->textureManager, *entities.at(j)));
                        entities.emplace_back(new Asteroid(data->textureManager, *entities.at(j)));
                        entities.at(i)->setHp(0);
                        entities.at(j)->setHp(0);
                        data->panel.addPoints(10);
                    }
                }
                if (entities.at(i)->getType() == EntityType::projectile &&
                    entities.at(j)->getType() == EntityType::rubble) {
                    if (Collision::PixelPerfectTest(entities.at(i)->getSprite(), entities.at(j)->getSprite())) {
                        entities.emplace_back(new Explosion(data->textureManager, *entities.at(j)));
                        entities.at(i)->setHp(0);
                        entities.at(j)->setHp(0);
                        data->panel.addPoints(7);
                    }
                }
            }
        }
    }
    for (int i = 0; i < entities.size(); i++) {
        if (data->spaceship.getDefenceStrategy()->getType() == none ||
            (data->spaceship.getDefenceStrategy()->getType() != none
             && !data->spaceship.getDefenceStrategy()->isVisible())) {
            if (entities.at(i)->getType() == EntityType::asteroid || entities.at(i)->getType() == EntityType::rubble) {
                if (Collision::PixelPerfectTest(entities.at(i)->getSprite(), data->spaceship.getSprite()) ||
                    Collision::PixelPerfectTest(entities.at(i)->getSprite(),
                                                data->spaceship.getDefenceStrategy()->getShieldSprite())) {
                    entities.emplace_back(new Explosion(data->textureManager, data->spaceship));
                    entities.emplace_back(new Explosion(data->textureManager, *entities.at(i)));
                    entities.at(i)->setHp(0);
                    isGameOver = true;
                }
            }
        }
        if (data->spaceship.getDefenceStrategy()->getType() != none &&
            data->spaceship.getDefenceStrategy()->isVisible()) {
            if (Collision::PixelPerfectTest(entities.at(i)->getSprite(),
                                            data->spaceship.getDefenceStrategy()->getShieldSprite())) {
                if (entities.at(i)->getType() == EntityType::asteroid) {
                    entities.emplace_back(new Asteroid(data->textureManager, *entities.at(i)));
                    entities.emplace_back(new Asteroid(data->textureManager, *entities.at(i)));
                }
                entities.emplace_back(new Explosion(data->textureManager, *entities.at(i)));
                entities.at(i)->setHp(0);
                data->panel.addPoints(-1);
                data->spaceship.getDefenceStrategy()->impact();
            }
        }
    }
    if (isGameOver && entities.at(entities.size()-1)->getAnimation().isEndOfAnim()) {
        data->stateManager.addState(StateRef(new GameOver(data)), true);
    }
}


void GameLoop::draw() {
    data->renderWindow.clear();
    data->renderWindow.draw(background);
    if(!isGameOver)
        data->spaceship.draw(data->renderWindow);
    if(data->spaceship.getDefenceStrategy()->getType() != none && data->spaceship.getDefenceStrategy()->isVisible() && !isGameOver)
        data->spaceship.getDefenceStrategy()->draw(data->spaceship.getSprite(), data->renderWindow);
    for(int i = 0; i < entities.size(); i++)
        if(entities.at(i)->getHp())
            entities.at(i)->draw(data->renderWindow);
    data->panel.draw(data->renderWindow);
    data->renderWindow.display();
}