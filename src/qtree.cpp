#include "../includes/simulation/world/qtree.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

auto QTree::draw_q(sf::RenderWindow &window) -> void {
    for (auto const &tile : tiles) {
        window.draw(tile.square);
    }
    for (auto const &child : children) {
        if (child) {
            child->draw_q(window);
        }
    }
}

auto QTree::subdivide() -> void {
    if (children[0] != nullptr)
        return;

    auto child_width = width / 2.0f;
    children[0] = std::make_unique<QTree>(x, y, child_width, child_width,
                                          level + 1, max_level, all_ants);
    children[1] =
        std::make_unique<QTree>(x + child_width, y, child_width, child_width,
                                level + 1, max_level, all_ants);
    children[2] =
        std::make_unique<QTree>(x, y + child_width, child_width, child_width,
                                level + 1, max_level, all_ants);
    children[3] =
        std::make_unique<QTree>(x + child_width, y + child_width, child_width,
                                child_width, level + 1, max_level, all_ants);

    for (const auto &ant : ants_contained) {
        for (int i = 0; i < 4; ++i) {
            if (within_tile(ant, tiles[i])) {
                children[i]->ants_contained.push_back(ant);
                break;
            }
        }
    }
    ants_contained.clear();
}

auto QTree::observe() -> void {
    if (ants_contained.size() >= capacity && children[0] == nullptr)
        subdivide();
    if (children[0] != nullptr) {
        for (auto const &child : children) {
            child->observe();
        }
    }
}

auto QTree::within_tile(const Ant &ant, const QTile &tile) -> bool {
    auto tile_x = tile.square.getPosition().x;
    auto tile_y = tile.square.getPosition().y;
    auto tile_width = tile.square.getSize().x;

    return ant.position.x >= tile_x && ant.position.x <= tile_x + tile_width &&
           ant.position.y >= tile_y && ant.position.y <= tile_y + tile_width;
}

auto QTree::collect_ants() -> void {
    if (children[0] != nullptr) {
        for (const auto &ant : ants_contained) {
            for (int i = 0; i < 4; ++i) {
                if (within_tile(ant, tiles[i])) {
                    children[i]->ants_contained.push_back(ant);
                    break;
                }
            }
        }
        ants_contained.clear();
    } else {
        for (auto const &ant : all_ants) {
            if (within_tile(ant, QTile(x, y, width))) {
                ants_contained.push_back(ant);
            }
        }
        if (ants_contained.size() >= capacity) {
            subdivide();
        }
    }
}
