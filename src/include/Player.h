//
// Created by Friedrich Tröscher on 08.02.25.
//

#ifndef CMAKESFMLPROJECT_PLAYER_H
#define CMAKESFMLPROJECT_PLAYER_H


#include <SFML/Graphics/RectangleShape.hpp>
#include "Direction.h"
#include "Projectile.h"
#include "MovementBounds.h"
#include "Combatant.h"

class Player : public Combatant {
public:
    //Constructor
    Player(sf::Vector2f size,
           sf::Vector2f position,
           MovementBounds movementBounds,
           float walkingSpeed,
           sf::Color color,
           float health,
           int level, std::vector<Projectile> projectiles);


    //Getters
    int getLevel() const;

    //Setters
    void setLevel(int value);

    void tick();


protected:


private:
    int level{};
};


#endif //CMAKESFMLPROJECT_PLAYER_H
