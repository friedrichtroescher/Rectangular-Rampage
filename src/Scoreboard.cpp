//
// Created by Friedrich Tröscher on 12.02.25.
//

#include "include/Scoreboard.h"
#include "include/Player.h"
#include "include/Game.h"


Scoreboard::Scoreboard() {
//    setHealth(100);
//    setLevel(1);
//    setSize({1280, 72});
//    setOutlineColor(sf::Color(100, 100, 100, 255));
//    setFillColor(sf::Color::Black);
//    setOutlineThickness(-5);
//
//    if (!pressStart2PRegular.openFromFile("fonts/PressStart2P-Regular.ttf")) {
//        // TODO Error handling
//    }
}

Scoreboard::Scoreboard(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, float outlineThickness,
                       sf::Color outlineColor, Game *game) {
    if (!pressStart2PRegular.openFromFile("fonts/PressStart2P-Regular.ttf")) {
        // TODO Error handling
    }
    setPosition(position);
    setSize(size);
    setFillColor(fillColor);
    setOutlineColor(outlineColor);
    setOutlineThickness(outlineThickness);
    this->game = game;
}


void Scoreboard::draw(sf::RenderWindow &window) {

    //outline
    window.draw(*this);

    //health bar text
    sf::Text healthText(pressStart2PRegular, "Health: ");
    healthText.setCharacterSize(20);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition({getPosition().x + getSize().x / 30.f,
                            getPosition().y + getSize().y / 2.f - healthText.getCharacterSize() / 2.f});

    //health bar indicator
    sf::RectangleShape healthBar({std::max(0.f, float(game->player.getHealth()) * 8.f), 20});
    healthBar.setPosition(
            {getPosition().x + healthText.getLocalBounds().size.x + healthText.getLocalBounds().size.x / 5,
             getPosition().y + getSize().y / 2.f - healthBar.getSize().y / 2.f});
    healthBar.setFillColor(sf::Color::Red);

    //Level indicator
    sf::Text levelText(pressStart2PRegular, "Level: " + std::to_string(game->player.getLevel()));
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition({getPosition().x + getSize().x - levelText.getLocalBounds().size.x - getSize().x / 30.f,
                           getPosition().y + getSize().y / 2.f - levelText.getCharacterSize() / 2.f});


    //draw the above initialized scoreboard elements
    window.draw(healthText);
    window.draw(healthBar);
    window.draw(levelText);
}
