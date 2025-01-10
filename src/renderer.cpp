#include "../includes/renderer/renderer.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

auto Renderer::render(sf::RenderTarget &target, Colony &colony, float &DT,
                      World &world, sf::RenderWindow &window) -> void {
    batch_ants(colony);
    batch_trails(colony);
    batch_food(world, target);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        world.food_creation(mouse_pos, window);
    }

    draw_batches(target);
}

auto Renderer::draw_batches(sf::RenderTarget &target) -> void {
    target.draw(ant_vertices);
    target.draw(trail_vertices);
    target.draw(food_vertices);
}

auto Renderer::batch_ants(const Colony &colony) -> void {
    ant_vertices.clear();

    for (auto const &ant : colony.get_ants()) {
        constexpr auto width = 2.0f;
        constexpr auto length = 7.0f;

        sf::Vector2f offset1(-width / 2, -length / 2);
        sf::Vector2f offset2(width / 2, -length / 2);
        sf::Vector2f offset3(width / 2, length / 2);
        sf::Vector2f offset4(-width / 2, length / 2);

        sf::Vector2f center_offset(0.0f, 0.0f);

        sf::Transform transform;
        transform.translate(ant.position);
        transform.rotate(ant.direction * 57.2958f + 90.0f);

        ant_vertices.append(
            sf::Vertex(transform.transformPoint(offset1), sf::Color::Green));
        ant_vertices.append(
            sf::Vertex(transform.transformPoint(offset2), sf::Color::Green));
        ant_vertices.append(
            sf::Vertex(transform.transformPoint(offset3), sf::Color::Green));
        ant_vertices.append(
            sf::Vertex(transform.transformPoint(offset4), sf::Color::Green));

        ant_vertices.append(sf::Vertex(transform.transformPoint(center_offset),
                                       sf::Color::Green));
    }
}

auto Renderer::batch_trails(const Colony &colony) -> void {
    trail_vertices.clear();

    for (auto const &ant : colony.get_ants()) {
        for (auto const &trail : ant.trails.get_buffer()) {
            trail_vertices.append(sf::Vertex(trail.get_pos(), sf::Color::Blue));
        }
    }
}

auto Renderer::batch_food(const World &world, sf::RenderTarget &target)
    -> void {
    for (auto const &food : world.foods) {
        sf::CircleShape food_shape(food.size);
        food_shape.setPosition(food.position);
        food_shape.setFillColor(sf::Color::Green);
        target.draw(food_shape);
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
