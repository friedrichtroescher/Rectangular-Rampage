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
        auto reloadingColor = sf::Color(
                0,
                255 - (float(remainingReloadTime) / float(totalReloadTime)) * 128.f,
                0,
                255);
        setFillColor(reloadingColor);
    } else {
        setFillColor(sf::Color::Green);
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
