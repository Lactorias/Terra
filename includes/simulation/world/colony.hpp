#ifndef COLONY
#define COLONY

#include "../ant/ant.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <cstdlib>
#include <vector>

class Colony {
public:
    Colony(float x, float y, int32_t num_ants)
        : position(x, y), num_ants(num_ants) {
        for (int32_t i = 0; i < num_ants; i++) {
            float rand_dir = static_cast<float>(rand() / RAND_MAX * 2.0f);
            ants.emplace_back(x, y, rand_dir, 10);
        }
    }

    auto get_ants() const -> const std::vector<Ant> &;

    auto get_pos() const -> const sf::Vector2f &;

    auto update(float DT) -> void;

    auto render(sf::RenderTarget &target) -> void;

private:
    std::vector<Ant> ants;
    sf::Vector2f position;
    const int32_t num_ants;
};

#endif // COLONY
