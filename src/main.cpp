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

    Colony colony(100, 100, 300);

    auto square_width = window.getSize().x / 2;

    World world;
    // 400 - 50, 400 - 50, 100
    //
    // proper fullscreen is
    // 5, 5, 790
    // QTile tile = QTile(0, 0, square_width);
    // QTile tile2 = QTile(square_width, 0, square_width);
    // QTile tile3 = QTile(0, square_width, square_width);
    // QTile tile4 = QTile(square_width, square_width, square_width);
    // QTile tile = QTile();
    //
    QTree qtree = QTree(0, 0, square_width, square_width, 0, 0);

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
        qtree.subdivide(0);
        qtree.subdivide(2);
        qtree.subdivide(1);
        qtree.subdivide(3);
        qtree.subdivide(0);
        qtree.draw_q(window);
        // window.draw(tile.square);
        // window.draw(tile2.square);
        // window.draw(tile3.square);
        // window.draw(tile4.square);

        window.display();
    }
}
