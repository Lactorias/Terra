#ifndef QTREE
#define QTREE

#include "../../renderer/texturemanager.hpp"
#include "../world/world.hpp"
#include "colony.hpp"
#include "food.hpp"
#include <array>
#include <cstdint>
#include <memory>
#include <raylib.h>
#include <unordered_set>
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
    QTile() {}

    QTile(float x, float y, float width) : x(x), y(y), width(width) {}

    auto draw() const -> void { DrawRectangleLines(x, y, width, width, RED); }

public:
    float x, y;
    float width;

public:
    bool visible = true;
};

class QTree {
public:
    QTree(float x, float y, float width, float height, int32_t level,
          int32_t max_level, World &world, Colony &colony)
        : x(x), y(y), width(width), height(height), level(level),
          max_level(max_level), m_world(world), m_colony(colony) {
        for (size_t i = 0; i < 4; i++)
            children[i] = nullptr;
        tile = QTile(x, y, width);
    }

    auto draw_q() -> void {
        if (tile.visible)
            tile.draw();
        for (auto const &child : children) {
            if (child) {
                child->draw_q();
            }
        }
    }

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

    auto collect_entities_s(std::unordered_set<int> &contained_entities,
                            std::vector<Food> &all_entities) -> void {
        for (auto const &entity : all_entities) {
            if (within_tile(entity, this->tile)) {
                contained_entities.insert(entity.id);
            }
        }
    };

    auto collect_trails() -> void;

    template <typename T>
    auto within_tile(const T &entity, const QTile &tile) -> bool {
        return entity.position.x >= tile.x &&
               entity.position.x < tile.x + tile.width &&
               entity.position.y >= tile.y &&
               entity.position.y < tile.y + tile.width;
    }

    template <has_pos T, has_pos_size V>
    auto entity_collison(const T &entity_one, const V &entity_two) -> bool {
        return entity_one.position.x >= entity_two.position.x &&
               entity_one.position.x <=
                   entity_two.position.x + entity_two.size &&
               entity_one.position.y >= entity_two.position.y &&
               entity_one.position.y <= entity_two.position.y + entity_two.size;
    }

    template <has_pos T, has_pos V>
    auto entity_collison_p(const T &entity_one, const V &entity_two) -> bool {
        auto const distance = std::sqrt(
            std::pow(entity_one.position.x - entity_two.position.x, 2) +
            std::pow(entity_one.position.y - entity_two.position.y, 2));

        return distance < 10.0f;
    }

    auto search_tiles() -> void;

    auto grab_food(Ant &ant, const Food &food) -> void;

    auto follow_trail(Ant &ant, const Trail &trail) -> void;

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
    std::vector<Ant> ants_contained{};
    std::unordered_set<int> foods_contained{};
    std::vector<Trail> trails_contained{};
    World &m_world;
    Colony &m_colony;
};

#endif // QTREE
