#pragma once
//
// Created by Friedrich Tröscher on 18.02.25.
//


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
    //this takes a vector and returns the direction that is closest to the vector
    static Direction getDirectionFromVector(sf::Vector2f vector);

    static float getDistanceFromVector(sf::Vector2f vector);

    static sf::Vector2f getNormalizedVector(sf::Vector2f vector);
};


