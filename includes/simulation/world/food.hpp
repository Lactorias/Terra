#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>

#pragma once

class Food {
public:
    sf::Vector2f position;
    constexpr static int32_t size = 3;

    Food(sf::Vector2f position) : position(position) {}

    void create_food(sf::RenderTarget &window) {
        sf::CircleShape food(size, 30);
        food.setPosition(position);
        food.setOrigin(size, size);
        food.setFillColor(sf::Color::Green);
        window.draw(food);
    }
};
