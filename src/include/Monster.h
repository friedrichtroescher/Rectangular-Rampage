//
// Created by Friedrich Tröscher on 14.02.25.
//

#ifndef CMAKESFMLPROJECT_MONSTER_H
#define CMAKESFMLPROJECT_MONSTER_H

#include "Combatant.h"

//Monster is a subclass of Combatant, implementing some functionality specific to monsters but common with Player Class
class Monster : public Combatant {
public:
    Monster();

    Monster(sf::Vector2f size,
            sf::Vector2f position,
            sf::RectangleShape movementBounds,
            float walkingSpeed,
            sf::Color color,
            float health, float damage, int totalReloadTime, Game *game);

    void tick() override;

    Combatant::Type getType() override;

protected:
private:
    sf::Vector2f calculatePlayerDirection();
};


#endif //CMAKESFMLPROJECT_MONSTER_H
