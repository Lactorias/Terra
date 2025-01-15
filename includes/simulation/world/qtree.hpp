#ifndef QTREE
#define QTREE

#include "../world/world.hpp"
#include "colony.hpp"
#include "food.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
concept has_pos_size = requires(T t) {
    t.position.x;
    t.position.y;
    t.size;
};

template <typename T>
concept has_pos = requires(T t) {
    t.position.x;
    t.position.y;
};

class QTile {
public:
    // x, y = size / 2 - width / 2
    // thickness 10
    QTile() {}

    QTile(float x, float y, float width) : x(x), y(y), width(width) {
        square = sf::RectangleShape(sf::Vector2f(width, width));
        square.setPosition(x, y);
        square.setFillColor(sf::Color::Transparent);
        square.setOutlineThickness(1);
        square.setOutlineColor(sf::Color::Red);
    }

    auto append_vertex(sf::VertexArray &vertex_array, sf::Color color) const
        -> void {
        vertex_array.append(sf::Vertex(sf::Vector2f(x, y), color));
        vertex_array.append(sf::Vertex(sf::Vector2f(x + width, y), color));

        vertex_array.append(sf::Vertex(sf::Vector2f(x + width, y), color));
        vertex_array.append(
            sf::Vertex(sf::Vector2f(x + width, y + width), color));

        vertex_array.append(
            sf::Vertex(sf::Vector2f(x + width, y + width), color));
        vertex_array.append(sf::Vertex(sf::Vector2f(x, y + width), color));

        vertex_array.append(sf::Vertex(sf::Vector2f(x, y + width), color));
        vertex_array.append(sf::Vertex(sf::Vector2f(x, y), color));
    }

private:
    float x, y;
    float width;
    int32_t border_width = 2;

public:
    bool visible = true;
    sf::RectangleShape square;
};

/*
 * Qtree, holds 4 qtree children
 *
 * each qtree, holds 4 qtiles
 *
 * someone... should know how many entities they hold, if tiles know, then they
 * can individually subdivide
 *
 * if the whole tree knows, then the whole tree subdivides, this is the current
 * bad behavior
 *
 * how can a tile signal that it should subdivide, that is our qtree's
 * funcionallity, and a qtile isnt a qtree
 *
 * a qtree should be a single tile, then have 4 qtrees which have their own
 * single tiles
 *
 * when we divide a specific quadtree child, it then forms its own 4 children
 *
 * the visibility of a qtile should be triggered if it was caused by a
 * subdivision, somehow
 *
 * or
 *
 * qtiles should always be visible, and the quadtree should be generated only if
 * needed
 *----------------------------------------------
 * Happy Design
 *
 * by doing this, we know simply draw a tile for each quadtree, and know exactly
 * what we hold, so we can issue a subdivision when needed and the drawing will
 * be handled for us as long as we subdivide the correct tree
 *
 *
 * pipeline:
 *
 * collect ants into qtree nodes/tiles
 *
 * on children which exceed capacity, subdivide them, otherwise dont
 *
 * repeat
 *
 *
 */

class QTree {
public:
    QTree(float x, float y, float width, float height, int32_t level,
          int32_t max_level, std::vector<Ant> &ants,
          const std::vector<Food> &foods, World &world, Colony &colony)
        : x(x), y(y), width(width), height(height), level(level),
          max_level(max_level), all_ants(ants), all_foods(foods),
          m_world(world), m_colony(colony) {
        for (size_t i = 0; i < 4; i++)
            children[i] = nullptr;
        auto child_width = width / 2;
        tile = QTile(x, y, width);
    }

    auto draw_q(sf::RenderWindow &window, sf::VertexArray &vertex_array)
        -> void;

    auto subdivide() -> void;

    auto observe() -> void;

    template <typename T>
    auto collect_entities(std::vector<T> &contained_entities,
                          std::vector<T> &all_entities) -> void {
        for (auto const &entity : all_entities) {
            if (within_tile(entity, this->tile)) {
                contained_entities.push_back(entity);
            }
        }
    };

    template <typename T>
    auto within_tile(const T &entity, const QTile &tile) -> bool {
        auto tile_x = tile.square.getPosition().x;
        auto tile_y = tile.square.getPosition().y;
        auto tile_width = tile.square.getSize().x;

        return entity.position.x >= tile_x &&
               entity.position.x < tile_x + tile_width &&
               entity.position.y >= tile_y &&
               entity.position.y < tile_y + tile_width;
    }

    template <has_pos T, has_pos_size V>
    auto entity_collison(const T &entity_one, const V &entity_two) -> bool {
        return entity_one.position.x >= entity_two.position.x &&
               entity_one.position.x <=
                   entity_two.position.x + entity_two.size &&
               entity_one.position.y >= entity_two.position.y &&
               entity_one.position.y <= entity_two.position.y + entity_two.size;
    }

    auto search_tiles() -> void;

    auto grab_food(Ant &ant, Food &food) -> void;

private:
    float x, y, width, height;
    int32_t level, max_level;

public:
    std::array<std::unique_ptr<QTree>, 4> children;

private:
    QTile tile;
    const int32_t capacity = 10;
    int32_t current_ants = 0;

public:
    std::vector<Ant> &all_ants;
    std::vector<Ant> ants_contained{};
    std::vector<Food> all_foods;
    std::vector<Food> foods_contained{};
    World &m_world;
    Colony &m_colony;
    // std::vector<Colony *> colonies;
};

#endif // QTREE
