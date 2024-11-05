#include "../ant/ant.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <cstdlib>
#include <vector>

#pragma once

class Colony {
public:
    std::vector<Ant> ants;
    sf::Vector2f position;

    Colony(float x, float y, int32_t num_ants)
        : position(x, y), num_ants(num_ants) {
        for (int32_t i = 0; i < num_ants; i++) {
            float rand_dir = static_cast<float>(rand() / RAND_MAX * 2.0f);
            ants.emplace_back(x, y, rand_dir);
        }
    }

    inline const std::vector<Ant> get_ants() { return ants; }
    inline sf::Vector2f get_pos() const { return position; }

    void update(float DT) {
        for (auto &ant : ants) {
            ant.update(DT);
        }
    }

    void render(sf::RenderTarget &target) {
        sf::CircleShape colony(20);
        colony.setPointCount(10);
        colony.setOrigin(20, 20);
        colony.setPosition(position);
        colony.setFillColor(sf::Color::Green);
        target.draw(colony);
    }

    const int32_t num_ants;
};
