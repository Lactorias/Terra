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
    static inline int32_t food_id = 0;
    int32_t id;
    constexpr static int32_t size = 9;

    Food(sf::Vector2f position) : position(position), id(food_id++) {}

    auto operator==(const Food &other) const -> bool {
        return this->id == other.id;
    }

    auto create_food(sf::RenderTarget &window) -> void;
};

#endif // FOOD
