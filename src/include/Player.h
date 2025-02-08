//
// Created by Friedrich Tröscher on 08.02.25.
//

#ifndef CMAKESFMLPROJECT_PLAYER_H
#define CMAKESFMLPROJECT_PLAYER_H


#include <SFML/Graphics/RectangleShape.hpp>
#include "Direction.h"
#include "Projectile.h"

class Player : public sf::RectangleShape {
public:
    //Constructor
    Player(sf::Vector2f size, sf::Vector2f position, sf::Color color, int health, int reloadTime);

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

protected:
    void setLastReloadLength(int lastReloadLength);

    int getLastReloadLength();

private:
    int health{};
    int reloadTime{};
    Direction direction;

    std::vector<Projectile> projectiles;
    int lastReloadLength;
};


#endif //CMAKESFMLPROJECT_PLAYER_H
