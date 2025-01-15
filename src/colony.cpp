#include "../includes/simulation/world/colony.hpp"
#include <SFML/System/Vector2.hpp>

auto Colony::get_ants() const -> const std::vector<Ant> & { return ants; }

auto Colony::get_ants() -> std::vector<Ant> & { return ants; }

auto Colony::get_pos() const -> const sf::Vector2f & { return position; }

auto Colony::update(float DT) -> void {
    for (auto &ant : ants) {
        ant.update(DT);
    }
}

auto Colony::render(sf::RenderTarget &target) -> void {
    sf::CircleShape colony(20);
    colony.setPointCount(10);
    colony.setOrigin(20, 20);
    colony.setPosition(position);
    colony.setFillColor(sf::Color::Green);
    target.draw(colony);
}
