#include "../includes/simulation/world/qtree.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

auto QTree::draw_q(sf::RenderWindow &window, sf::VertexArray &vertex_array)
    -> void {
    for (auto const &tile : tiles) {
        tile.append_vertex(vertex_array, sf::Color::Red);
    }
    for (auto const &child : children) {
        if (child) {
            child->draw_q(window, vertex_array);
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
    children[0] =
        std::make_unique<QTree>(x, y, child_width, child_width, level + 1,
                                max_level, all_ants, all_foods);
    children[1] =
        std::make_unique<QTree>(x + child_width, y, child_width, child_width,
                                level + 1, max_level, all_ants, all_foods);
    children[2] =
        std::make_unique<QTree>(x, y + child_width, child_width, child_width,
                                level + 1, max_level, all_ants, all_foods);
    children[3] = std::make_unique<QTree>(x + child_width, y + child_width,
                                          child_width, child_width, level + 1,
                                          max_level, all_ants, all_foods);

    for (const auto &ant : ants_contained) {
        for (int i = 0; i < 4; ++i) {
            if (within_tile(ant, tiles[i])) {
                children[i]->ants_contained.push_back(ant);
                break;
            }
        }
    }

    for (const auto &food : foods_contained) {
        for (int i = 0; i < 4; ++i) {
            if (within_tile(food, tiles[i])) {
                children[i]->foods_contained.push_back(food);
                break;
            }
        }
    }

    ants_contained.clear();
    foods_contained.clear();
}

auto QTree::observe() -> void {
    if ((ants_contained.size() >= capacity ||
         foods_contained.size() >= capacity) &&
        children[0] == nullptr)
        subdivide();
    if (children[0] != nullptr) {
        for (auto const &child : children) {
            child->observe();
        }
    }
}
