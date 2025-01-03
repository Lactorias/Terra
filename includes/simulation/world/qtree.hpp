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
        square.setOutlineThickness(border_width);
        square.setOutlineColor(sf::Color::Red);
    }

private:
    float x, y;
    float width;
    int32_t border_width = 2;

public:
    sf::RectangleShape square;
};

class QTree {
public:
    QTree(float x, float y, float width, float height, int32_t level,
          int32_t max_level, const std::vector<Ant> &ants,
          const std::vector<Food> &foods)
        : x(x), y(y), width(width), height(height), level(level),
          max_level(max_level), all_ants(ants), all_foods(foods) {
        for (size_t i = 0; i < 4; i++)
            children[i] = nullptr;
        auto child_width = width / 2;
        tiles[0] = QTile(x, y, child_width);
        tiles[1] = QTile(x + child_width, y, child_width);
        tiles[2] = QTile(x, y + child_width, child_width);
        tiles[3] = QTile(x + child_width, y + child_width, child_width);
    }

    auto draw_q(sf::RenderWindow &window) -> void;

    auto subdivide() -> void;

    auto observe() -> void;

    template <typename T>
    auto collect_entities(std::vector<T> &contained_entities,
                          std::vector<T> &all_entities,
                          std::vector<T> QTree::*child_container) -> void {
        if (children[0] != nullptr) {
            for (const auto &entity : contained_entities) {
                for (int i = 0; i < 4; ++i) {
                    if (within_tile(entity, tiles[i])) {
                        (children[i].get()->*child_container).push_back(entity);
                        break;
                    }
                }
            }
            contained_entities.clear();
        } else {
            for (auto const &entity : all_entities) {
                if (within_tile(entity, QTile(x, y, width))) {
                    contained_entities.push_back(entity);
                }
            }
            // if (contained_entities.size() >= capacity) {
            //     subdivide();
            // }
        }
    };

    template <typename T>
    auto within_tile(const T &entity, const QTile &tile) -> bool {
        auto tile_x = tile.square.getPosition().x;
        auto tile_y = tile.square.getPosition().y;
        auto tile_width = tile.square.getSize().x;

        return entity.position.x >= tile_x &&
               entity.position.x <= tile_x + tile_width &&
               entity.position.y >= tile_y &&
               entity.position.y <= tile_y + tile_width;
    }

    auto grab_food(Ant &ant, Food &food) -> void;

private:
    float x, y, width, height;
    int32_t level, max_level;
    std::array<std::unique_ptr<QTree>, 4> children;
    std::array<QTile, 4> tiles;
    const int32_t capacity = 10;
    int32_t current_ants = 0;

public:
    std::vector<Ant> all_ants;
    std::vector<Ant> ants_contained{};
    std::vector<Food> all_foods;
    std::vector<Food> foods_contained{};
    // std::vector<Colony *> colonies;
};

#endif // QTREE
