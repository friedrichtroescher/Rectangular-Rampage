//
// Created by Friedrich Tröscher on 05.02.25.
//

#ifndef CMAKESFMLPROJECT_PROJECTILE_H
#define CMAKESFMLPROJECT_PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Direction.h"
#include "Combatant.h"

class Game;

class Projectile : public sf::RectangleShape {
public:
    //Constructor
    Projectile(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Vector2f velocity, int timeout,
               Combatant::Type shotBy, float damage,
               Game *game);

    //Getters
    sf::Vector2f getVelocity();

    int getTimeout();

    static sf::Vector2f generateFixedDirectionVelocity(Direction direction, float speed);

    //Setters
    void setVelocity(sf::Vector2f velocity);

    void setTimeout(int timeout);

protected:
private:
    sf::Vector2f velocity;
    int timeout;
    Game *game;
    Combatant::Type shotBy;
    float damage;
public:
    float getDamage() const;

    void setDamage(float damage);

public:
    Combatant::Type getShotBy();

    void setShotBy(Combatant::Type shotBy);
};


#endif //CMAKESFMLPROJECT_PROJECTILE_H
