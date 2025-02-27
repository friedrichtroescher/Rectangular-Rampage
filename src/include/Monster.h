//
// Created by Friedrich Tröscher on 14.02.25.
//

#ifndef CMAKESFMLPROJECT_MONSTER_H
#define CMAKESFMLPROJECT_MONSTER_H

#include "Combatant.h"

class Monster : public Combatant {
public:
    Monster();

    Monster(sf::Vector2f size,
            sf::Vector2f position,
            MovementBounds movementBounds,
            float walkingSpeed,
            sf::Color color,
            float health, float damage, int totalReloadTime, Game *game);

    void tick() override;

    Combatant::Type getType();

protected:
private:
    sf::Vector2f calculatePlayerDirection();
};


#endif //CMAKESFMLPROJECT_MONSTER_H
