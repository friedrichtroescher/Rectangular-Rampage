//
// Created by Friedrich Tröscher on 14.02.25.
//

#include "include/Monster.h"
#include "include/Game.h"

Monster::Monster() : Combatant() {}

Monster::Monster(sf::Vector2f size,
                 sf::Vector2f position,
                 sf::RectangleShape movementBounds,
                 float walkingSpeed,
                 sf::Color color,
                 float health, float damage, int totalReloadTime, Game *game)
        :
        Combatant(size, position, movementBounds, walkingSpeed, color, health, damage, totalReloadTime, game) {}

void Monster::tick() {
    if (game == nullptr) {
        throw std::runtime_error("Monster has no game reference");
    }

    //update Monster shooting timeout and animation
    if (remainingReloadTime > 0) {
        remainingReloadTime--;

        //Color changes from a dark green to a bright green as the reload completes
        auto reloadingColor = sf::Color(
                0,
                255.f - (float(remainingReloadTime) / float(totalReloadTime)) * 200.f,
                0,
                255);
        setFillColor(reloadingColor);
    } else {
        //if the monster is not reloading, it shoots in a precise direction (not just the 8 directions the player can shoot in) at the player
        //the shootPrecisely method takes care of normalizing the direction vector and multiplying it by the speed
        shootPrecisely({5, 5}, 120, sf::Color::Green, 5,
                       calculatePlayerDirection());
    }


    //move the Monster towards the player if it is further than 5x player size away
    //Assumes square player
    sf::Vector2f playerDirection = calculatePlayerDirection();
    if (DirectionUtils::getDistanceFromVector(playerDirection) > 5 * game->getPlayer().getSize().x) {
        walk(DirectionUtils::getDirectionFromVector(playerDirection), getWalkingSpeed());
    }
}


sf::Vector2f Monster::calculatePlayerDirection() {
    if (game == nullptr) {
        throw std::runtime_error("Monster has no game reference");
    }
    return {
            game->getPlayer().getPosition() - getPosition()
    };
}

Combatant::Type Monster::getType() {
    return Combatant::Type::Monster;
}


