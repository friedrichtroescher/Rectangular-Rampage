//
// Created by Friedrich Tröscher on 09.02.25.
//

#include "include/MovementBounds.h"

MovementBounds::MovementBounds(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

sf::Vector2f MovementBounds::getTopLeftBound() {
    return topLeft;
}

sf::Vector2f MovementBounds::getBottomRightBound() {
    return bottomRight;
}

void MovementBounds::setTopLeftBound(sf::Vector2f vector2f) {
    this->topLeft = vector2f;
}

void MovementBounds::setBottomRightBound(sf::Vector2f vector2f) {
    this->bottomRight = vector2f;
}

void MovementBounds::setBounds(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}


MovementBounds MovementBounds::getBounds() {
    return {topLeft, bottomRight};
}
