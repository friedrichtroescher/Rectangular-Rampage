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

    Scoreboard(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, float outlineThickness,
               sf::Color outlineColor, Game *game);

    void draw(sf::RenderWindow &window);

protected:
private:
    float health{};
    int level{};
    sf::Font pressStart2PRegular;
    Game *game;
};


#endif //CMAKESFMLPROJECT_SCOREBOARD_H
