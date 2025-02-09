//
// Created by Friedrich Tröscher on 08.02.25.
//

#ifndef CMAKESFMLPROJECT_PLAYER_H
#define CMAKESFMLPROJECT_PLAYER_H


#include <SFML/Graphics/RectangleShape.hpp>
#include "Direction.h"
#include "Projectile.h"
#include "MovementBounds.h"

class Player : public sf::RectangleShape, public MovementBounds {
public:
    //Constructor
    Player(sf::Vector2f size, sf::Vector2f position, MovementBounds movementBounds, float walkingSpeed, sf::Color color,
           int health,
           int reloadTime);

    //Getters
    int getHealth();

    int getReloadTime();

    Direction getDirection();

    std::vector<Projectile> getProjectiles();

    //Setters
    void setHealth(int health);

    void setReloadTime(int reloadTime);

    void setDirection(Direction direction);

    void setProjectiles(std::vector<Projectile> projectiles);

    void shoot(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed, int reloadTime);

    void tick();

    void draw(sf::RenderWindow &window);

    void walk(Direction direction, float distance);

    float boundDistance(Direction direction);

    float getWalkingSpeed();

    float setWalkingSpeed(float value);

protected:
    void setLastReloadLength(int lastReloadLength);

    int getLastReloadLength();

private:
    int health{};
    int reloadTime{};
    Direction direction;
    std::vector<Projectile> projectiles;
    int lastReloadLength;
    float walkingSpeed;
};


#endif //CMAKESFMLPROJECT_PLAYER_H
