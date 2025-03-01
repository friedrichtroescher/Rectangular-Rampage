//
// Created by Friedrich Tröscher on 12.02.25.
//

#include "include/Scoreboard.h"
#include "include/Player.h"
#include "include/Game.h"


Scoreboard::Scoreboard() {
}

Scoreboard::Scoreboard(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, float outlineThickness,
                       sf::Color outlineColor, Game *game) {
    if (!pressStart2PRegular.openFromFile("fonts/PressStart2P-Regular.ttf")) {
        throw std::runtime_error("Could not load font");
    }
    setPosition(position);
    setSize(size);
    setFillColor(fillColor);
    setOutlineColor(outlineColor);
    setOutlineThickness(outlineThickness);
    setGame(game);
}


void Scoreboard::draw(sf::RenderWindow &window) {
    //variables that are used multiple times in the following calculations
    sf::Vector2f position = getPosition();
    sf::Vector2f size = getSize();
    unsigned int textSize = 20;
    float playerHealth = getGame()->getPlayer().getHealth();

    //health bar text
    sf::Text healthText(pressStart2PRegular, "Health: ");
    healthText.setCharacterSize(textSize);
    healthText.setFillColor(sf::Color::Red);
    healthText.setPosition({position.x + size.x / 30.f,
                            position.y + size.y / 2.f - float(textSize) / 2.f});

    //health bar indicator
    sf::RectangleShape healthBar({std::max(0.f, playerHealth * 8.f), 20});
    healthBar.setPosition(
            {position.x + healthText.getLocalBounds().size.x + healthText.getLocalBounds().size.x / 5,
             position.y + size.y / 2.f - healthBar.getSize().y / 2.f});
    healthBar.setFillColor(sf::Color::Red);

    //Level indicator
    sf::Text levelText(pressStart2PRegular, "Level: " + std::to_string(getGame()->getPlayer().getLevel()));
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition({position.x + size.x - levelText.getLocalBounds().size.x - size.x / 30.f,
                           position.y + size.y / 2.f - float(textSize) / 2.f});


    //draw the scoreboard elements
    window.draw(*this); //the outline
    window.draw(healthText);
    window.draw(healthBar);
    window.draw(levelText);
}

[[maybe_unused]] float Scoreboard::getHealth() const {
    return health;
}

[[maybe_unused]] void Scoreboard::setHealth(float value) {
    health = value;
}

[[maybe_unused]] int Scoreboard::getLevel() const {
    return level;
}

[[maybe_unused]] void Scoreboard::setLevel(int value) {
    level = value;
}

[[maybe_unused]] sf::Font Scoreboard::getPressStart2PRegular() {
    return pressStart2PRegular;
}

[[maybe_unused]] void Scoreboard::setPressStart2PRegular(const sf::Font &pointer) {
    pressStart2PRegular = pointer;
}

Game *Scoreboard::getGame() const {
    return game;
}

void Scoreboard::setGame(Game *pointer) {
    game = pointer;
}
