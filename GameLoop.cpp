#include "GameLoop.h"
#include "Definitions.h"
#include <utility>
#include <iostream>
#include "Asteroid.h"
#include "GameOver.h"
#include "Pause.h"

GameLoop::GameLoop(GameDataRef dataRef) {
    data = std::move(dataRef);
}

GameLoop::~GameLoop() {
    int n = entities.size();
    for (int i = 0; i < n; i++)
        delete(entities.at(i));
    n = aliens.size();
    for (int i = 0; i < n; i++)
        delete(aliens.at(i));
}

void GameLoop::init() {
    for (int i = 0; i < INITIAL_ASTEROIDS; i++) {
        entities.emplace_back(new Asteroid(data->textureManager));
    }
    data->panel = {data->font, data->textureManager};
    gameOver = false;
    data->soundManager.playGameTheme();
    background.setTexture(data->textureManager.getTextureFromAtlas("background"));
    background.setOrigin(0,0);
    genTimer.init();
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
    genTimer.update();
    data->panel.setShieldText(data->spaceship.getDefenceStrategy()->getShieldLife());
    for (int k = 0; k < entities.size(); k++) {
        entities.at(k)->update();
        if (!entities.at(k)->isAlive()) {
            entities.erase(entities.begin() + k);
        }
    }
    if(!gameOver){
        if (genTimer.getAsteroidGenTime() >= ASTEROID_SPAWN) {
            entities.emplace_back(new Asteroid(data->textureManager));
            data->panel.addPoints(POINT_BONUS);
            genTimer.resetAsteroidGen();
        }
        if (genTimer.getAlienGenTime() >= ALIEN_SPAWN) {
            aliens.emplace_back(new Alien(data->textureManager));
            data->panel.addPoints(POINT_BONUS);
            genTimer.resetAlienGen();
        }
        for (int k = 0; k < aliens.size(); k++) {
            aliens.at(k)->update(data-> textureManager, data->spaceship, entities, data->soundManager);
            if (!aliens.at(k)->isAlive()) {
                aliens.erase(aliens.begin() + k);
            }
        }
        if (data->spaceship.isShooting()) {
            entities.emplace_back(new Projectile(data->textureManager, data->spaceship.getSprite(), true));
            data->panel.addPoints(POINT_MALUS);
        }
        for (int i = 0; i < entities.size(); i++) {
            for(int j = 0; j < aliens.size(); j++){
                if(entities.at(i)->getType() == EntityType::projectile){
                    if(Collision::PixelPerfectTest(entities.at(i)->getSprite(), aliens.at(j)->getSprite())){
                        entities.emplace_back(new Explosion(data->textureManager, *aliens.at(j)));
                        data->soundManager.playExplosionSound();
                        entities.at(i)->terminate();
                        aliens.at(j)->terminate();
                        data->panel.addPoints(ALIEN_EXPL);
                    }
                }
            }
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
                    entities.at(i)->getType() == EntityType::rubble ||
                    entities.at(i)->getType() == EntityType::alien_ammo) {
                    if (Collision::PixelPerfectTest(entities.at(i)->getSprite(), data->spaceship.getSprite()) ||
                        Collision::PixelPerfectTest(entities.at(i)->getSprite(),
                                                    data->spaceship.getDefenceStrategy()->getShieldSprite())) {
                        data->soundManager.pauseBoostSound();
                        data->soundManager.playExplosionSound();
                        entities.emplace_back(new Explosion(data->textureManager, data->spaceship));
                        gameOverTimer.restart();
                        gameOver = true;
                    }
                }
            }
            if (data->spaceship.getDefenceStrategy()->getType() != none &&
                data->spaceship.getDefenceStrategy()->isVisible() &&
                entities.at(i)->getType() != EntityType::projectile &&
                entities.at(i)->getType() != EntityType::alien) {
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
    if (gameOver && gameOverTimer.getElapsedTime().asSeconds() >= TIME_BEFORE_GAMEOVER) {
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
    for(int i = 0; i < entities.size(); i++) {
        if (entities.at(i)->isAlive())
            entities.at(i)->draw(data->renderWindow);
    }
    for(int i = 0; i < aliens.size(); i++) {
        if (aliens.at(i)->isAlive())
            aliens.at(i)->draw(data->renderWindow);
    }
    data->panel.draw(data->renderWindow);
    data->renderWindow.display();
}