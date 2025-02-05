//
// Created by Friedrich Tröscher on 05.02.25.
//

#ifndef CMAKESFMLPROJECT_MOVINGRECTANGLE_H
#define CMAKESFMLPROJECT_MOVINGRECTANGLE_H

#include <SFML/Graphics.hpp>

class MovingRectangle : public sf::RectangleShape {
public:
    //Constructor
    MovingRectangle(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Vector2f velocity, int timeout);

    //Getters
    sf::Vector2f getVelocity();

    int getTimeout();

    //Setters
    void setVelocity(sf::Vector2f velocity);

    void setTimeout(int timeout);

protected:
private:
    sf::Vector2f velocity;
    int timeout;

};


#endif //CMAKESFMLPROJECT_MOVINGRECTANGLE_H
