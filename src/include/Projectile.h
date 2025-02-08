//
// Created by Friedrich Tröscher on 05.02.25.
//

#ifndef CMAKESFMLPROJECT_PROJECTILE_H
#define CMAKESFMLPROJECT_PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Direction.h"

class Projectile : public sf::RectangleShape {
public:
    //Constructor
    Projectile(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Vector2f velocity, int timeout);

    //Getters
    sf::Vector2f getVelocity();

    int getTimeout();

    static sf::Vector2f generateVelocity(Direction direction, float speed);

    //Setters
    void setVelocity(sf::Vector2f velocity);

    void setTimeout(int timeout);

protected:
private:
    sf::Vector2f velocity;
    int timeout;

};


#endif //CMAKESFMLPROJECT_PROJECTILE_H
