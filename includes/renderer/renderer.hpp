#include "../simulation/world/colony.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

class Renderer {
public:
    Renderer() {}

    void render(sf::RenderTarget &target, Colony &colony, float &DT) {
        render_colony(target, colony);
        for (auto ant : colony.get_ants()) {
            render_ant(target, ant);
        }
    }

    void render_colony(sf::RenderTarget &target, Colony &colony_circle) {
        sf::CircleShape colony(20);
        colony.setPointCount(10);
        colony.setOrigin(20, 20);
        colony.setPosition(colony_circle.get_pos());
        colony.setFillColor(sf::Color::Green);
        target.draw(colony);
    }

    void render_ant(sf::RenderTarget &target, Ant &ant) {
        const float width = 2.0f;
        const float length = 7.0f;
        sf::RectangleShape body(sf::Vector2f(width, length));
        body.setOrigin(width * 0.5f, length * 0.5f);
        body.setPosition(ant.position);
        body.setRotation(ant.direction * 57.2958f + 90.0f);
        body.setFillColor(sf::Color::Green);
        target.draw(body);
    }
};
