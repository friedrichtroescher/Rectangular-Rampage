//
// Created by Friedrich Tröscher on 12.02.25.
//

#ifndef CMAKESFMLPROJECT_SCOREBOARD_H
#define CMAKESFMLPROJECT_SCOREBOARD_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Scoreboard : public sf::RectangleShape {
public:
    Scoreboard(int health, int level);

    void draw(sf::RenderWindow &window);

    void setHealth(int value);

    void setLevel(int value);

    int getHealth();

    int getLevel();

    void update(Player &player);

protected:
private:
    int health{};
    int level{};
    sf::Font pressStart2PRegular;
};


#endif //CMAKESFMLPROJECT_SCOREBOARD_H
