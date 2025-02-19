//
// Created by Friedrich Tröscher on 14.02.25.
//

#include "include/Monster.h"
#include "include/Direction.h"

Monster::Monster(sf::Vector2f size,
                 sf::Vector2f position,
                 MovementBounds movementBounds,
                 float walkingSpeed,
                 sf::Color color,
                 float health, float damage, int totalReloadTime, std::vector<Projectile> &projectiles, Player
                 &targetedPlayer)
        :
        Combatant(size, position, movementBounds, walkingSpeed, color, health, damage, totalReloadTime,
                  projectiles), targetedPlayer(targetedPlayer) {

};

void Monster::tick() {
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
        float projectileSpeed = 3;
        sf::Vector2f projectileVector = DirectionUtils::getNormalizedVector(calculatePlayerDirection()) *
                                        projectileSpeed;

        shootPrecisely({5, 5}, 120, sf::Color::Green, 5,
                       projectileVector);
    }

    sf::Vector2f playerDirection = calculatePlayerDirection();

    //move the Monster towards the player if it is further than 5x player size away
    //Assumes square player
    if (DirectionUtils::getDistanceFromVector(playerDirection) > 5 * targetedPlayer.getSize().x) {
        walk(DirectionUtils::getDirectionFromVector(playerDirection), getWalkingSpeed());
    }
}


sf::Vector2f Monster::calculatePlayerDirection() {
    return {
            targetedPlayer.getPosition() - getPosition()
    };
}
