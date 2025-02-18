//
// Created by Friedrich Tröscher on 14.02.25.
//

#include "include/Monster.h"

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
        setFillColor(sf::Color::White);
    }

    //move Monster towards targetedPlayer position





}


sf::Vector2f Monster::calculatePlayerDirection() {
    return {
            targetedPlayer.getPosition() - getPosition()
    };
}
