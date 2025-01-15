#include "../includes/simulation/world/qtree.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>
#include <memory>
using std::find;

auto QTree::draw_q(sf::RenderWindow &window, sf::VertexArray &vertex_array)
    -> void {
    if (tile.visible)
        tile.append_vertex(vertex_array, sf::Color::Red);
    for (auto const &child : children) {
        if (child) {
            child->draw_q(window, vertex_array);
        }
    }
}

// recursively check tiles, call search tiles on children
auto QTree::search_tiles() -> void {
    // run ant against all other food, only in this region, O(nlogn)!
    for (auto &ant : ants_contained) {
        for (auto &food : foods_contained) {
            if (entity_collison(ant, food)) {
                grab_food(ant, food);
            }
        }
    }

    for (auto const &child : children) {
        if (child) {
            child->search_tiles();
        }
    }
}

auto QTree::subdivide() -> void {
    if (children[0] != nullptr)
        return;
    if (level == max_level) {
        return;
    }
    level++;
    auto child_width = width / 2.0f;
    children[0] = std::make_unique<QTree>(x, y, child_width, child_width,
                                          level + 1, max_level, all_ants,
                                          all_foods, m_world, m_colony);
    children[1] = std::make_unique<QTree>(
        x + child_width, y, child_width, child_width, level + 1, max_level,
        all_ants, all_foods, m_world, m_colony);
    children[2] = std::make_unique<QTree>(
        x, y + child_width, child_width, child_width, level + 1, max_level,
        all_ants, all_foods, m_world, m_colony);
    children[3] = std::make_unique<QTree>(
        x + child_width, y + child_width, child_width, child_width, level + 1,
        max_level, all_ants, all_foods, m_world, m_colony);

    for (const auto &ant : ants_contained) {
        for (int i = 0; i < 4; ++i) {
            if (within_tile(ant, children[i]->tile)) {
                children[i]->ants_contained.push_back(ant);
                break;
            }
        }
    }

    for (const auto &food : foods_contained) {
        for (int i = 0; i < 4; ++i) {
            if (within_tile(food, children[i]->tile)) {
                children[i]->foods_contained.push_back(food);
                break;
            }
        }
    }

    ants_contained.clear();
    foods_contained.clear();
}

auto QTree::observe() -> void {
    if (children[0] == nullptr && (ants_contained.size() >= capacity ||
                                   foods_contained.size() >= capacity)) {
        subdivide();
    }
    if (children[0] != nullptr) {
        for (auto const &child : children) {
            child->observe();
        }
    }
}

auto QTree::grab_food(Ant &ant, Food &food) -> void {
    auto it_ant =
        find(begin(m_colony.get_ants()), end(m_colony.get_ants()), ant);
    if (!it_ant->has_food) {
        it_ant->has_food = true;

        auto it = find(begin(foods_contained), end(foods_contained), food);
        auto it_to_world = find(begin(m_world.foods), end(m_world.foods), food);

        if (it != end(foods_contained)) {
            foods_contained.erase(it);
        }
        if (it != end(m_world.foods)) {
            m_world.foods.erase(it_to_world);
        }
    }
}
