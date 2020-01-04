cmake_minimum_required(VERSION 3.2)
project(xenon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(unit_test)

set(SOURCE_FILES main.cpp GameLoop.cpp TextureManager.cpp Animation.cpp Entity.cpp
        Asteroid.cpp Spaceship.cpp Projectile.cpp Explosion.cpp Collision.cpp Panel.cpp
        State.cpp StateManager.cpp Game.cpp Splash.cpp MainMenu.cpp SelectSpaceShip.cpp
        GameOver.cpp Pause.cpp DefenceStrategy.cpp ToggableShield.cpp TimeShield.cpp
        NoneShield.cpp Definitions.h)

add_executable(xenon ${SOURCE_FILES})
add_library(core ${SOURCE_FILES})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(xenon ${SFML_LIBRARIES})
endif()