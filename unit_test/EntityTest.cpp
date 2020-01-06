#include "../Spaceship.h"
#include "cmath"
#include "../Definitions.h"
#include "gtest/gtest.h"
#include "../TextureManager.h"
#include "../Asteroid.h"

TextureManager textureManager;

TEST(Spaceship, Lennon) {
    Spaceship spaceship(textureManager, lennon);
    EXPECT_EQ(WINDOW_WIDTH / 2. - LENNON_SPRITE_WIDTH / 2., spaceship.getSprite().getPosition().x);
    EXPECT_EQ(WINDOW_HEIGHT / 2. - LENNON_SPRITE_HEIGHT / 2., spaceship.getSprite().getPosition().y);
    EXPECT_EQ(true, spaceship.isAlive());

}

TEST(Spaceship, Macca){
    Spaceship spaceship(textureManager, macca);
    EXPECT_EQ(WINDOW_WIDTH / 2. - MACCA_SPRITE_WIDTH / 2., spaceship.getSprite().getPosition().x);
    EXPECT_EQ(WINDOW_HEIGHT / 2. - MACCA_SPRITE_HEIGHT / 2., spaceship.getSprite().getPosition().y);
    EXPECT_EQ(true, spaceship.isAlive());
}

TEST(Spaceship, Harrison){
    Spaceship spaceship(textureManager, harrison);
    EXPECT_EQ(WINDOW_WIDTH / 2. - HARRISON_SPRITE_WIDTH / 2., spaceship.getSprite().getPosition().x);
    EXPECT_EQ(WINDOW_HEIGHT / 2. - HARRISON_SPRITE_HEIGHT / 2., spaceship.getSprite().getPosition().y);
    EXPECT_EQ(true, spaceship.isAlive());
}

TEST(Spaceship, Starr){
    Spaceship spaceship(textureManager, starr);
    EXPECT_EQ(WINDOW_WIDTH / 2. - STARR_SPRITE_WIDTH / 2., spaceship.getSprite().getPosition().x);
    EXPECT_EQ(WINDOW_HEIGHT / 2. - STARR_SPRITE_HEIGHT / 2., spaceship.getSprite().getPosition().y);
    EXPECT_EQ(true, spaceship.isAlive());
}

TEST(Method, terminate){
    Entity* entity;
    entity = new Asteroid(textureManager);
    entity->terminate();
    EXPECT_EQ(false, entity->isAlive());
    delete entity;
}