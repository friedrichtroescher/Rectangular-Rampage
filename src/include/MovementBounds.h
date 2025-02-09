//
// Created by Friedrich Tröscher on 09.02.25.
//

#ifndef CMAKESFMLPROJECT_MOVEMENTBOUNDS_H
#define CMAKESFMLPROJECT_MOVEMENTBOUNDS_H

#include <SFML/Graphics.hpp>

class MovementBounds {
public:
    MovementBounds(sf::Vector2f topLeft, sf::Vector2f bottomRight);

    MovementBounds getBounds();

    sf::Vector2f getTopLeftBound();

    sf::Vector2f getBottomRightBound();

protected:
    void setBounds(sf::Vector2f topLeft, sf::Vector2f bottomRight);

    void setTopLeftBound(sf::Vector2f vector2f);

    void setBottomRightBound(sf::Vector2f vector2f);

private:
    sf::Vector2f topLeft;
    sf::Vector2f bottomRight;
};


#endif //CMAKESFMLPROJECT_MOVEMENTBOUNDS_H
