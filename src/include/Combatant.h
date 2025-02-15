//
// Created by Friedrich Tröscher on 15.02.25.
//

#ifndef CMAKESFMLPROJECT_COMBATANT_H
#define CMAKESFMLPROJECT_COMBATANT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "MovementBounds.h"
#include "Direction.h"
#include "Projectile.h"


class Combatant : public sf::RectangleShape, public MovementBounds {
public:
    float getHealth();

    int getReloadTime();

    Direction getDirection();

    float getWalkingSpeed();

    int getLastReloadLength();

    void setLastReloadLength(int value);

    void setHealth(float value);

    void setReloadTime(int value);

    void setDirection(Direction value);

    float setWalkingSpeed(float value);

    virtual void tick() = 0;

    void draw(sf::RenderWindow &window);

    void walk(Direction direction, float distance);

    float boundDistance(Direction direction);

    void shoot(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed, int reloadTime);

protected:
    Combatant(sf::Vector2f size, sf::Vector2f position, MovementBounds movementBounds, float walkingSpeed,
              sf::Color color,
              float health, std::vector<Projectile> &projectiles);

    float health;
    int reloadTime;
    Direction direction;
    int lastReloadLength;
    float walkingSpeed;
    std::vector<Projectile> projectiles;
private:
};


#endif //CMAKESFMLPROJECT_COMBATANT_H
