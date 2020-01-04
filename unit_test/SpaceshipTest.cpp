#include "../Spaceship.h"
#include "cmath"
#include "../Definitions.h"
#include "gtest/gtest.h"
#include "../TextureManager.h"


TEST(SpaceshipTest, Constructor){
    TextureManager textureManager;
    Spaceship Lennon(textureManager, lennon);
    EXPECT_EQ((ShipType)lennon, (ShipType)Lennon.getType());
    EXPECT_EQ((float)LENNON_FIRE_RATE, Lennon.getFireRate());

}