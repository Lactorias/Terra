#include "../includes/renderer/renderer.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

auto Renderer::render(sf::RenderTarget &target, Colony &colony, float &DT,
                      World &world, sf::RenderWindow &window) -> void {
    render_colony(target, colony);
    for (auto &ant : colony.get_ants()) {
        render_ant(target, ant);
        for (auto &trail : ant.trails) {
            render_trail(target, trail);
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        world.food_creation(mouse_pos, window);
    }
    for (auto &food : world.foods) {
        render_food(target, food);
    }
}

auto Renderer::render_colony(sf::RenderTarget &target,
                             const Colony &colony_circle) -> void {
    sf::CircleShape colony(20);
    colony.setPointCount(10);
    colony.setOrigin(20, 20);
    colony.setPosition(colony_circle.get_pos());
    colony.setFillColor(sf::Color::Green);
    target.draw(colony);
}

auto Renderer::render_ant(sf::RenderTarget &target, const Ant &ant) -> void {
    constexpr float width = 2.0f;
    constexpr float length = 7.0f;
    sf::RectangleShape body(sf::Vector2f(width, length));
    body.setOrigin(width * 0.5f, length * 0.5f);
    body.setPosition(ant.position);
    body.setRotation(ant.direction * 57.2958f + 90.0f);
    body.setFillColor(sf::Color::Green);
    target.draw(body);
}

auto Renderer::render_food(sf::RenderTarget &target, const Food &food_l)
    -> void {
    sf::RectangleShape food(sf::Vector2f(food_l.size, food_l.size));
    food.setPosition(food_l.position);
    food.setOrigin(food_l.size, food_l.size);
    food.setFillColor(sf::Color::Green);
    target.draw(food);
}

auto Renderer::render_trail(sf::RenderTarget &target, const Trail &trail)
    -> void {
    sf::CircleShape traill(3);
    traill.setPointCount(10);
    traill.setOrigin(20, 20);
    traill.setPosition(trail.get_pos());
    traill.setFillColor(sf::Color::Blue);
    target.draw(traill);
}
