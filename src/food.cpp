#include "../includes/simulation/world/food.hpp"

auto Food::create_food(sf::RenderTarget &window) -> void {
    sf::CircleShape food(size, 30);
    food.setPosition(position);
    food.setOrigin(size, size);
    food.setFillColor(sf::Color::Green);
    window.draw(food);
}
