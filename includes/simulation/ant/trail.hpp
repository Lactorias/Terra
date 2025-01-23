#ifndef TRAIL
#define TRAIL

#include "raylib.h"

enum class Trail_Type : int {
    WANDER,
    HOME,
};

class Trail {
public:
    Trail() = default;

    Trail(float x, float y) : position(x, y) {}

    auto get_pos() const -> const Vector2 & { return position; }

    Vector2 position;

public:
    Trail_Type trail_type{Trail_Type::WANDER};
};

#endif // TRAIL
