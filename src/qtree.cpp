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

auto QTree::subdivide(int index) -> void {
    auto child_width = width / 2.0f;
    // fix memory leak!!!!!!!!!!!!!!!
    children[index] = std::make_unique<QTree>(
        tiles[index].square.getPosition().x,
        tiles[index].square.getPosition().y, child_width, child_width, 0, 0);
}
