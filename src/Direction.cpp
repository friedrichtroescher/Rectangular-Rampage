//
// Created by Friedrich Tröscher on 18.02.25.
//

#include "include/Direction.h"

Direction DirectionUtils::getDirectionFromVector(sf::Vector2f vector) {
    float radian = atan2(vector.y, vector.x);

    //using the radian, we roughly determine the direction (based on the circle divided in 8 parts)

    if (radian >= -M_PI / 8 && radian < M_PI / 8) {
        return Direction::RIGHT;
    } else if (radian >= M_PI / 8 && radian < 3 * M_PI / 8) {
        return Direction::DOWN_RIGHT;
    } else if (radian >= 3 * M_PI / 8 && radian < 5 * M_PI / 8) {
        return Direction::DOWN;
    } else if (radian >= 5 * M_PI / 8 && radian < 7 * M_PI / 8) {
        return Direction::DOWN_LEFT;
    } else if (radian >= 7 * M_PI / 8 || radian < -7 * M_PI / 8) {
        return Direction::LEFT;
    } else if (radian >= -7 * M_PI / 8 && radian < -5 * M_PI / 8) {
        return Direction::UP_LEFT;
    } else if (radian >= -5 * M_PI / 8 && radian < -3 * M_PI / 8) {
        return Direction::UP;
    } else if (radian >= -3 * M_PI / 8 && radian < -M_PI / 8) {
        return Direction::UP_RIGHT;
    }

    return Direction::NONE;
}

float DirectionUtils::getDistanceFromVector(sf::Vector2f vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f DirectionUtils::getNormalizedVector(sf::Vector2f vector) {
    float magnitude = getDistanceFromVector(vector);

    //return normalized vector
    return {vector.x / magnitude, vector.y / magnitude};
}
