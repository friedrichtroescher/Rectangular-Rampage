#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);

    sf::RectangleShape rectangle;
    rectangle.setSize({10, 10});
    rectangle.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        // Draw here

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            rectangle.setPosition({rectangle.getPosition().x + 1, rectangle.getPosition().y});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            rectangle.setPosition({rectangle.getPosition().x - 1, rectangle.getPosition().y});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            rectangle.setPosition({rectangle.getPosition().x, rectangle.getPosition().y - 1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            rectangle.setPosition({rectangle.getPosition().x, rectangle.getPosition().y + 1});
        }

        window.draw(rectangle);

        window.display();
    }
}
