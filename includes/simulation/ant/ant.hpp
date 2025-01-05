#ifndef ANT
#define ANT

#include "trail.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

class Ant {
public:
    Ant(float x, float y, float angle)
        : position(x, y), direction(angle), direction_time_elapsed(0.0f) {}

    auto update(const float DT) -> void;

    auto update_position(const float DT) -> void;

    auto check_boundaries() -> void;

    auto new_direction() -> void;

    auto get_rand_range(float width) -> float;

    auto render(sf::RenderTarget &target) -> void;

    constexpr auto lerp_angle(float start, float end, float t) -> float;

    std::vector<Trail> trails;
    sf::Vector2f position;
    float direction;
    float target_direction;
    float direction_time_elapsed;
    float trail_time_elapsed{};
    constexpr static float direction_time_period = 0.5f;
    constexpr static float PI = 3.14159265f;
    const int32_t map_height = 800;
    const int32_t map_width = 800;
    float turn_speed = 3.0f;
};

#endif // ANT
