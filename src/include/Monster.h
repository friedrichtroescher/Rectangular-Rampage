//
// Created by Friedrich Tröscher on 14.02.25.
//

#ifndef CMAKESFMLPROJECT_MONSTER_H
#define CMAKESFMLPROJECT_MONSTER_H


#include "Player.h"

class Monster : public Combatant {
public:
    Monster(sf::Vector2f size,
            sf::Vector2f position,
            MovementBounds movementBounds,
            float walkingSpeed,
            sf::Color color,
            float health, float damage, int totalReloadTime, std::vector<Projectile> &projectiles, Player &targetedPlayer);

    void tick();


protected:
private:
    Player &targetedPlayer;

    sf::Vector2f calculatePlayerDirection();
};


#endif //CMAKESFMLPROJECT_MONSTER_H
