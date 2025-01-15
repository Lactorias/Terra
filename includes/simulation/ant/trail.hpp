#ifndef TRAIL
#define TRAIL

#include <SFML/System/Vector2.hpp>
class Trail {
public:
    Trail() = default;

    Trail(float x, float y) : position(x, y) {}

    auto get_pos() const -> const sf::Vector2f & { return position; }

    sf::Vector2f position;

public:
    enum class Trail_Type : int {
        WANDER,
        HOME,
    };

public:
    Trail_Type trail_type{Trail_Type::WANDER};
};

#endif // TRAIL
