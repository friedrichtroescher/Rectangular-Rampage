//
// Created by Friedrich Tröscher on 12.02.25.
//

#ifndef CMAKESFMLPROJECT_SCOREBOARD_H
#define CMAKESFMLPROJECT_SCOREBOARD_H

#include <SFML/Graphics.hpp>

class Scoreboard : public sf::RectangleShape {
public:
    Scoreboard(int health, int level);

    void draw(sf::RenderWindow &window);

    void setHealth(int value);

    void setLevel(int value);

    int getHealth();

    int getLevel();

protected:
private:
    int health{};
    int level{};
};


#endif //CMAKESFMLPROJECT_SCOREBOARD_H
