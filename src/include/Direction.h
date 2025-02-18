//
// Created by Friedrich Tröscher on 18.02.25.
//

#ifndef CMAKESFMLPROJECT_DIRECTION_H
#define CMAKESFMLPROJECT_DIRECTION_H

#include <SFML/Graphics.hpp>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    NONE
};

class DirectionUtils {
public:
    static Direction getDirectionFromVector(sf::Vector2f vector);

    static float getDistanceFromVector(sf::Vector2f vector);
};


#endif //CMAKESFMLPROJECT_DIRECTION_H
