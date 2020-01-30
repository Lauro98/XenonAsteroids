#include <SFML/Window/Event.hpp>
#include "../Spaceship.h"
#include "../Definitions.h"
#include "gtest/gtest.h"
#include "../TextureManager.h"


TEST(Spaceship, Lennon) {
    TextureManager textureManager;
    Spaceship spaceship(textureManager, lennon);
    EXPECT_EQ(WINDOW_WIDTH / 2., spaceship.getSprite().getPosition().x);
    EXPECT_EQ(WINDOW_HEIGHT / 2., spaceship.getSprite().getPosition().y);
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
    EXPECT_EQ(true, spaceship.isAlive());
    EXPECT_EQ(false, spaceship.isShooting());
}

TEST(Spaceship, Macca){
    TextureManager textureManager;
    Spaceship spaceship(textureManager, macca);
    EXPECT_EQ(WINDOW_WIDTH / 2., spaceship.getSprite().getPosition().x);
    EXPECT_EQ(WINDOW_HEIGHT / 2., spaceship.getSprite().getPosition().y);
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
    EXPECT_EQ(true, spaceship.isAlive());
    EXPECT_EQ(false, spaceship.isShooting());
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
}

TEST(Spaceship, Harrison){
    TextureManager textureManager;
    Spaceship spaceship(textureManager, harrison);
    EXPECT_EQ(WINDOW_WIDTH / 2., spaceship.getSprite().getPosition().x);
    EXPECT_EQ(WINDOW_HEIGHT / 2., spaceship.getSprite().getPosition().y);
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
    EXPECT_EQ(true, spaceship.isAlive());
    EXPECT_EQ(false, spaceship.isShooting());
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
}

TEST(Spaceship, Starr){
    TextureManager textureManager;
    Spaceship spaceship(textureManager, starr);
    EXPECT_EQ(WINDOW_WIDTH / 2., spaceship.getSprite().getPosition().x);
    EXPECT_EQ(WINDOW_HEIGHT / 2., spaceship.getSprite().getPosition().y);
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
    EXPECT_EQ(true, spaceship.isAlive());
    EXPECT_EQ(false, spaceship.isShooting());
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
}

TEST(DefenceStrategy, ToggableShield){
    TextureManager textureManager;
    Spaceship spaceship(textureManager, lennon);
    spaceship.setDefenceStrategy(toggableShield);
    EXPECT_EQ(DefStrategyType::toggableShield, spaceship.getDefenceStrategy()->getType());
    EXPECT_EQ(spaceship.getSprite().getPosition(), spaceship.getDefenceStrategy()->getShieldSprite().getPosition());
    EXPECT_EQ(1, spaceship.getDefenceStrategy()->getShieldLife());
    EXPECT_EQ(false, spaceship.getDefenceStrategy()->isVisible());
    spaceship.getDefenceStrategy()->activateShield();
    EXPECT_EQ(true, spaceship.getDefenceStrategy()->isVisible());
    spaceship.getDefenceStrategy()->activateShield();
    EXPECT_EQ(false, spaceship.getDefenceStrategy()->isVisible());
    spaceship.getDefenceStrategy()->activateShield();
    spaceship.getDefenceStrategy()->addShield();
    EXPECT_EQ(2, spaceship.getDefenceStrategy()->getShieldLife());
    spaceship.getDefenceStrategy()->impact();
    EXPECT_EQ(false, spaceship.getDefenceStrategy()->isVisible());
    EXPECT_EQ(1, spaceship.getDefenceStrategy()->getShieldLife());
    spaceship.getDefenceStrategy()->impact();
    spaceship.getDefenceStrategy()->update();
    EXPECT_EQ(true, spaceship.getDefenceStrategy()->isShieldTerminated());
    spaceship.update();
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
}

TEST(DefenceStrategy, TimeShield){
    TextureManager textureManager;
    Spaceship spaceship(textureManager, lennon);
    spaceship.setDefenceStrategy(timeShield);
    EXPECT_EQ(DefStrategyType::timeShield, spaceship.getDefenceStrategy()->getType());
    EXPECT_EQ(spaceship.getSprite().getPosition(), spaceship.getDefenceStrategy()->getShieldSprite().getPosition());
    EXPECT_EQ(TIME_SHIELD_BASE_DURATION, spaceship.getDefenceStrategy()->getShieldLife());
    EXPECT_EQ(false, spaceship.getDefenceStrategy()->isVisible());
    spaceship.getDefenceStrategy()->activateShield();
    EXPECT_EQ(true, spaceship.getDefenceStrategy()->isVisible());
    spaceship.getDefenceStrategy()->activateShield();
    EXPECT_EQ(true, spaceship.getDefenceStrategy()->isVisible());
    spaceship.getDefenceStrategy()->addShield();
    EXPECT_GT(spaceship.getDefenceStrategy()->getShieldLife(), TIME_SHIELD_BASE_DURATION);
    EXPECT_EQ(true, spaceship.getDefenceStrategy()->isVisible());
    while(spaceship.getDefenceStrategy()->getShieldLife() != 0) {
        spaceship.getDefenceStrategy()->update();
    }
    EXPECT_EQ(true, spaceship.getDefenceStrategy()->isShieldTerminated());
    EXPECT_EQ(false, spaceship.getDefenceStrategy()->isVisible());
    spaceship.update();
    EXPECT_EQ(DefStrategyType::none, spaceship.getDefenceStrategy()->getType());
}