#include "../includes/simulation/world/food.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

auto Food::create_food(sf::RenderTarget &window) -> void {
    constexpr float width = 3.0f;
    sf::RectangleShape square(sf::Vector2f(width, width));
    square.setOrigin(width * 0.5f, width * 0.5f);
    square.setPosition(position);
    square.setFillColor(sf::Color::Green);
    // sf::CircleShape food(size, 30);
    // food.setPosition(position);
    // food.setOrigin(size, size);
    // food.setFillColor(sf::Color::Green);
    // window.draw(square);
}
