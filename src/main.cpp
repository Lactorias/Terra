#include "../includes/renderer/renderer.hpp"
#include "../includes/simulation/ant/ant.hpp"
#include "../includes/simulation/world/colony.hpp"
#include "../includes/simulation/world/world.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(0)));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Ant Simulator - Terra",
                            sf::Style::Default, settings);

    Colony colony(100, 100, 300);

    World world;

    Renderer renderer;

    window.setFramerateLimit(144);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        float dt = clock.restart().asSeconds();

        colony.update(dt);

        window.clear();

        renderer.render(window, colony, dt, world, window);

        window.display();
    }
}
