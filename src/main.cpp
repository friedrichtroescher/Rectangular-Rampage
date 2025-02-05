#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    float PosX = 0;
    float PosY = 0;

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);

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
        // draw a random shape

        sf::RectangleShape rectangle;
        rectangle.setSize({10, 10});
        rectangle.setFillColor(sf::Color::White);
        rectangle.setPosition({PosX, PosY});
        window.draw(rectangle);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            PosX++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            PosX--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            PosY--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            PosY++;
        }

        window.display();
    }
}
