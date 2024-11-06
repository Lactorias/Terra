#include "../simulation/world/colony.hpp"
#include "../simulation/world/world.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

class Renderer {
public:
    Renderer() {}

    void render(sf::RenderTarget &target, Colony &colony, float &DT,
                World &world, sf::RenderWindow &window) {
        render_colony(target, colony);
        for (auto ant : colony.get_ants()) {
            render_ant(target, ant);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            world.food_creation(mouse_pos, window);
        }
        for (auto food : world.foods) {
            render_food(target, food);
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

    void render_food(sf::RenderTarget &target, Food &food_l) {
        sf::CircleShape food(food_l.size, 30);
        food.setPosition(food_l.position);
        food.setOrigin(food_l.size, food_l.size);
        food.setFillColor(sf::Color::Green);
        target.draw(food);
    }
};
