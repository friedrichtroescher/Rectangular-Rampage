//
// Created by Friedrich Tröscher on 08.02.25.
//

#include <SFML/Graphics.hpp>
#include "include/Input.h"

Direction Input::getWASDDirection() {
    const bool up =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    const bool right =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    const bool down =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
    const bool left =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);

    if (up && right) {
        return Direction::UP_RIGHT;
    } else if (right && down) {
        return Direction::DOWN_RIGHT;
    } else if (down && left) {
        return Direction::DOWN_LEFT;
    } else if (left && up) {
        return Direction::UP_LEFT;
    } else if (up) {
        return Direction::UP;
    } else if (right) {
        return Direction::RIGHT;
    } else if (down) {
        return Direction::DOWN;
    } else if (left) {
        return Direction::LEFT;
    }
    return Direction::NONE;
}

bool Input::isShooting() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}
