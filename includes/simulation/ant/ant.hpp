#ifndef ANT
#define ANT

#include "../circularbuffer.hpp"
#include "raylib.h"
#include "trail.hpp"
#include <cmath>

class Ant {
public:
    Ant() = default;

    Ant(float x, float y, float angle)
        : trails(), position(x, y), direction(angle),
          direction_time_elapsed(0.0f), id(ant_id++) {}

    auto update(const float DT) -> void;

    auto update_position(const float DT) -> void;

    auto check_boundaries() -> void;

    auto new_direction() -> void;

    auto get_rand_range(float width) -> float;

    constexpr auto lerp_angle(float start, float end, float t) -> float;

    auto operator==(const Ant &other) const -> bool {
        return this->id == other.id;
    }

    Trail_Type dropping_trail{Trail_Type::WANDER};
    CircularBuffer<Trail, 100> trails;
    Vector2 position;
    float direction;
    float target_direction;
    float direction_time_elapsed;
    float trail_time_elapsed{};
    constexpr static float direction_time_period = 0.5f;
    // constexpr static float PI = 3.14159265f;
    int32_t map_height = 800;
    int32_t map_width = 800;
    float turn_speed = 3.0f;
    bool has_food = false;
    static inline int32_t ant_id = 0;
    int32_t id;
};

#endif // ANT
