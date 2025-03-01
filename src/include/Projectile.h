#pragma once
//
// Created by Friedrich Tröscher on 05.02.25.
//


#include <SFML/Graphics.hpp>
#include "Direction.h"
#include "Combatant.h"

class Game;

class Projectile : public sf::RectangleShape {
public:
    Projectile(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Vector2f velocity, int timeout,
               Combatant::Type shotBy, float damage,
               Game *game);

    sf::Vector2f getVelocity();

    int getTimeout();

    static sf::Vector2f generateFixedDirectionVelocity(Direction direction, float speed);

    void setVelocity(sf::Vector2f velocity);

    void setTimeout(int timeout);

    float getDamage() const;

    void setDamage(float damage);

    Combatant::Type getShotBy();

    void setShotBy(Combatant::Type shotBy);

    Game *getGame() const;

protected:
private:
    sf::Vector2f velocity;

    int timeout;

    Game *game;

    Combatant::Type shotBy;

    float damage;

    void setGame(Game *game);
};


