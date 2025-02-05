//
// Created by Friedrich Tröscher on 05.02.25.
//

#include "MovingRectangle.h"

MovingRectangle::MovingRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Vector2f velocity,
                                 int timeout) {
    setSize(size);
    setPosition(position);
    setFillColor(color);
    setVelocity(velocity);
    setTimeout(timeout);
}

sf::Vector2f MovingRectangle::getVelocity() {
    return this->velocity;
}

void MovingRectangle::setVelocity(sf::Vector2f velocity) {
    this->velocity = velocity;
}

int MovingRectangle::getTimeout() {
    return this->timeout;
}

void MovingRectangle::setTimeout(int timeout) {
    this->timeout = timeout;
}
