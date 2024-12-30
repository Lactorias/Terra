#ifndef QTREE
#define QTREE

#include "colony.hpp"
#include "food.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstdint>
#include <memory>
#include <vector>

class QTile {
public:
    // x, y = size / 2 - width / 2
    // thickness 10
    QTile() {}

    QTile(float x, float y, float width) : x(x), y(y), width(width) {
        square = sf::RectangleShape(sf::Vector2f(width, width));
        square.setPosition(x, y);
        square.setFillColor(sf::Color::Transparent);
        square.setOutlineThickness(10);
        square.setOutlineColor(sf::Color::Red);
    }

private:
    float x, y;
    float width;
    int32_t border_width = 10;

public:
    sf::RectangleShape square;
};

class QTree {
public:
    std::vector<Ant *> ants;
    // std::vector<Food *> food;
    // std::vector<Colony *> colonies;

    QTree(float x, float y, float width, float height, int32_t level,
          int32_t max_level)
        : x(x), y(y), width(width), height(height), level(level),
          max_level(max_level) {
        for (size_t i = 0; i < 4; i++)
            children[i] = nullptr;
        tiles[0] = QTile(0, 0, width);
        tiles[1] = QTile(width, 0, width);
        tiles[2] = QTile(0, width, width);
        tiles[3] = QTile(width, width, width);
    }

    auto draw_q(sf::RenderWindow &window) -> void;

    auto subdivide(int index) -> void;

private:
    float x, y, width, height;
    int32_t level, max_level;
    std::array<std::unique_ptr<QTree>, 4> children;
    std::array<QTile, 4> tiles;
    const int32_t capacity = 4;
};

#endif // QTREE
