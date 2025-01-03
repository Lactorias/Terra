#ifndef TRAIL
#define TRAIL

#include <SFML/System/Vector2.hpp>
class Trail {
public:
    Trail(float x, float y) : position(x, y) {}

    auto get_pos() const -> sf::Vector2f { return position; }

private:
    sf::Vector2f position;
};

#endif // TRAIL
