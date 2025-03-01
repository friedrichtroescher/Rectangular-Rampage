//
// Created by Friedrich Tröscher on 08.02.25.
//

#ifndef CMAKESFMLPROJECT_PLAYER_H
#define CMAKESFMLPROJECT_PLAYER_H

#include "Combatant.h"

//Player is a subclass of Combatant, implementing some functionality specific to the player but common with Monster Class
class Player : public Combatant {
public:
    Player();

    //Constructor
    Player(sf::Vector2f size, sf::Vector2f position, sf::RectangleShape movementBounds, float walkingSpeed,
           sf::Color color,
           float health, float damage, int totalReloadTime, int level, Game *game);


    //Getters
    int getLevel() const;

    //Setters
    void setLevel(int value);

    void tick();

    Combatant::Type getType();


protected:


private:
    int level{};
};


#endif //CMAKESFMLPROJECT_PLAYER_H
