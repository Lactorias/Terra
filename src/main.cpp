#include "../includes/renderer/renderer.hpp"
#include "../includes/simulation/ant/ant.hpp"
#include "../includes/simulation/world/colony.hpp"
#include "../includes/simulation/world/qtree.hpp"
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

    Colony colony(100, 100, 10);

    auto square_width = window.getSize().x / 2;

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
        QTree qtree = QTree(0, 0, square_width * 2, square_width * 2, 0, 0,
                            colony.get_ants(), world.foods);
        qtree.collect_entities(qtree.ants_contained, qtree.all_ants,
                               &QTree::ants_contained);
        qtree.collect_entities(qtree.foods_contained, qtree.all_foods,
                               &QTree::foods_contained);
        qtree.observe();
        qtree.draw_q(window);
        window.display();
    }
}
