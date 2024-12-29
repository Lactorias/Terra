#ifndef FOOD
#define FOOD

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>

class Food {
public:
    sf::Vector2f position;
    constexpr static int32_t size = 3;

    Food(sf::Vector2f position) : position(position) {}

    auto create_food(sf::RenderTarget &window) -> void;
};

#endif // FOOD
