#ifndef WORLD
#define WORLD

#include "colony.hpp"
#include "food.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstdint>
#include <vector>

class World {
public:
    std::vector<Food> foods;
    // std::vector<Walls> walls;
    World() {}

    void food_creation(const sf::Vector2i position, sf::RenderWindow &window) {
        const sf::Vector2f mouse_pos = window.mapPixelToCoords(position);
        foods.emplace_back(mouse_pos);
    }
};

#endif // WORLD
