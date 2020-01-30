#include "../Panel.h"
#include "gtest/gtest.h"

TEST(Panel, score){
    sf::Font font;
    TextureManager textureManager;
    Panel panel(font, textureManager);
    EXPECT_EQ(0, panel.getScore());
    panel.addPoints(-2);
    EXPECT_EQ(0, panel.getScore());
    panel.addPoints(10);
    EXPECT_EQ(10, panel.getScore());
    panel.addPoints(-1);
    EXPECT_EQ(9, panel.getScore());
}