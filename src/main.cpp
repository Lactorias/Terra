#include "../includes/renderer/renderer.hpp"
#include "../includes/simulation/ant/ant.hpp"
#include "../includes/simulation/world/colony.hpp"
#include "../includes/simulation/world/qtree.hpp"
#include "../includes/simulation/world/world.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <functional>
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(0)));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Ant Simulator - Terra",
                            sf::Style::Default, settings);

    Colony colony(100, 100, 30);

    Renderer renderer;

    auto const square_width = window.getSize().x / 2;

    World world;

    sf::VertexArray lines(sf::Lines);

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
        QTree qtree = QTree(0, 0, square_width * 2, square_width * 2, 0, 8,
                            colony.get_ants(), world.foods, world, colony);

        qtree.collect_entities(qtree.ants_contained, qtree.all_ants);

        qtree.collect_entities(qtree.foods_contained, qtree.all_foods);

        qtree.observe();

        qtree.search_tiles();
        lines.clear();
        qtree.draw_q(window, lines);
        window.draw(lines);
        window.display();
    }
}
