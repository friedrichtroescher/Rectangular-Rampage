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

    Direction getDirection();

    float getWalkingSpeed();

    int getRemainingReloadTime();

    int getTotalReloadTime();

    float getDamage();

    void setTotalReloadTime(int value);

    void setHealth(float value);

    void setDirection(Direction value);

    float setWalkingSpeed(float value);

    void setDamage(float value);

    virtual void tick() = 0;

    void draw(sf::RenderWindow &window);

    void walk(Direction direction, float distance);

    float boundDistance(Direction direction);

    void shoot(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed);

    void shootPrecisely(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed, sf::Vector2f
    projectileMovement);

    void setRemainingReloadTime(int value);

protected:
    Combatant(sf::Vector2f size, sf::Vector2f position, MovementBounds movementBounds, float walkingSpeed,
              sf::Color color,
              float health, float damage, int totalReloadTime, std::vector<Projectile> &projectiles);


    float health{};
    float damage{};
    int remainingReloadTime{};
    int totalReloadTime{};
    Direction direction;
    float walkingSpeed{};
    std::vector<Projectile> &projectiles;
private:
};


#endif //CMAKESFMLPROJECT_COMBATANT_H
