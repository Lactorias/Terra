#ifndef ANT
#define ANT

#include "../circularbuffer.hpp"
#include "trail.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

class Ant {
public:
    Ant(float x, float y, float angle, int32_t trail_capacity)
        : position(x, y), direction(angle), direction_time_elapsed(0.0f),
          trails(trail_capacity), id(ant_id++) {}

    auto update(const float DT) -> void;

    auto update_position(const float DT) -> void;

    auto check_boundaries() -> void;

    auto new_direction() -> void;

    auto get_rand_range(float width) -> float;

    auto render(sf::RenderTarget &target) -> void;

    constexpr auto lerp_angle(float start, float end, float t) -> float;

    auto operator==(const Ant &other) const -> bool {
        return this->id == other.id;
    }

    CircularBuffer<Trail> trails;
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
    bool has_food = false;
    static inline int32_t ant_id = 0;
    int32_t id;
};

#endif // ANT
