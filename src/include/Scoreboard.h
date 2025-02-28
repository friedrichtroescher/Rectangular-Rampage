//
// Created by Friedrich Tröscher on 12.02.25.
//

#ifndef CMAKESFMLPROJECT_SCOREBOARD_H
#define CMAKESFMLPROJECT_SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include "Player.h"

//Scoreboard is a class that displays the health and level of the player. It should only be drawn with the draw method, never with window.draw(scoreboard)
class Scoreboard : public sf::RectangleShape {
public:
    Scoreboard();

    void draw(sf::RenderWindow &window);

    void setHealth(float value);

    void setLevel(int value);

    float getHealth();

    int getLevel();

    //updates the scoreboard with the player's health and level
    void update(Player &player);

protected:
private:
    float health{};
    int level{};
    sf::Font pressStart2PRegular;
    Game *game;
};


#endif //CMAKESFMLPROJECT_SCOREBOARD_H
