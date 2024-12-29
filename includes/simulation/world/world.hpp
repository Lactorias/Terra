#include "colony.hpp"
#include "food.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstdint>
#include <vector>

#pragma once

class QTree {
public:
    std::vector<Ant *> ants;
    std::vector<Food *> food;
    std::vector<Colony *> colonies;

    QTree(float x, float y, float width, float height, int32_t level,
          int32_t max_level)
        : x(x), y(y), width(width), height(height), level(level),
          max_level(max_level) {
        for (size_t i = 0; i < 4; i++)
            children[i] = nullptr;
    }

private:
    float x, y, width, height;
    int32_t level, max_level;
    std::array<QTree *, 4> children;
    const int32_t capacity = 4;
};

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
