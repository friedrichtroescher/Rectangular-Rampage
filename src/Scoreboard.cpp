//
// Created by Friedrich Tröscher on 12.02.25.
//

#include "include/Scoreboard.h"

Scoreboard::Scoreboard(int health, int level) {
    setHealth(health);
    setLevel(level);
    setSize({1280, 72});
    setOutlineColor(sf::Color(100, 100, 100, 255));
    setFillColor(sf::Color::Black);
    setOutlineThickness(-5);

}

void Scoreboard::setHealth(int value) {
    if (value < 0 || value > 100) {
        return;
    }
    health = value;
}

void Scoreboard::setLevel(int value) {
    if (value < 0) {
        return;
    }
    level = value;
}

int Scoreboard::getHealth() {
    return health;
}

int Scoreboard::getLevel() {
    return level;
}

void Scoreboard::draw(sf::RenderWindow &window) {
    // a scoreboard that displays the health as a rectangle and the level as a "Level: int level" text
    sf::RectangleShape healthBar({float(getHealth()), 10});
    healthBar.setPosition(
            {getPosition().x + getSize().x / 10.f, getPosition().y + getSize().y / 2.f - healthBar.getSize().y});
    healthBar.setFillColor(sf::Color::Red);
    window.draw(*this);
    window.draw(healthBar);


//    sf::Font font;
//    font.loadFromFile("arial.ttf");
//    sf::Text levelText("Level: " + std::to_string(level), font);
//    levelText.setPosition(10, 30);
//    window.draw(levelText);
//

}
