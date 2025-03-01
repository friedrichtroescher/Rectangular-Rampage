#pragma once
//
// Created by Friedrich Tröscher on 15.02.25.
//


#include <SFML/Graphics/RectangleShape.hpp>
#include "Direction.h"


//this forward declaration is necessary to avoid an issue with circular dependencies in the game class
class Game;

class Projectile;

class Combatant : public sf::RectangleShape {
public:
    enum class Type {
        Player, Monster, Unknown
    };

    virtual Combatant::Type getType() = 0;

    float getHealth() const;

    Direction getDirection();

    float getWalkingSpeed() const;

    int getRemainingReloadTime() const;

    int getTotalReloadTime() const;

    float getDamage() const;

    void setTotalReloadTime(int value);

    void setHealth(float value);

    void setDirection(Direction value);

    void setWalkingSpeed(float value);

    void setDamage(float value);

    virtual void tick() = 0;

    void walk(Direction walkingDirection, float distance);

    float boundDistance(Direction boundDirectionFromCombatant);

    //shoots a projectile in the direction the Combatant is facing, this is not precise
    void shoot(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed);

    //shoots a projectile in the direction specified by projectileMovement, adjusted to speed specified
    //this was implemented to allow Monsters to target the player precisely, but could be implemented for the player as well
    void shootPrecisely(sf::Vector2f projectileSize, int timeout, sf::Color color, float speed, sf::Vector2f
    projectileDirection);

    void setRemainingReloadTime(int value);

    [[maybe_unused]] Game *getGame() const;

    void setGame(Game *pointer);

protected:
    Combatant();

    Combatant(sf::Vector2f size, sf::Vector2f position, sf::RectangleShape movementBounds, float walkingSpeed,
              sf::Color color,
              float health, float damage, int totalReloadTime, Game *game);

    float health{};
    float damage{};
    int remainingReloadTime{};
    int totalReloadTime{};
    Direction direction;
    float walkingSpeed{};
    sf::RectangleShape movementBounds;
public:
    const RectangleShape &getMovementBounds() const;

    void setMovementBounds(const RectangleShape& rectangleShape);

protected:
    //pointer to the game object, so that the Combatant can interact with other game elements
    Game *game;
private:
};


