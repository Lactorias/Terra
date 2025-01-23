#ifndef FOOD
#define FOOD

#include "raylib.h"
#include <cstdint>

class Food {
public:
    Vector2 position;
    static inline int32_t food_id = 0;
    int32_t id;
    constexpr static int32_t size = 9;
    Food() = default;

    Food(Vector2 position) : position(position), id(food_id++) {}

    auto operator==(const Food &other) const -> bool {
        return this->id == other.id;
    }

    auto render() const -> void { DrawCircleV(position, size, GREEN); }
};

#endif // FOOD
