#ifndef RENDERER
#define RENDERER

#include "../simulation/world/colony.hpp"
#include "../simulation/world/world.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

class Renderer {
public:
    Renderer() {}

    auto render(sf::RenderTarget &target, Colony &colony, float &DT,
                World &world, sf::RenderWindow &window) -> void;

private:
    auto render_colony(sf::RenderTarget &target, const Colony &colony_circle)
        -> void;

    auto render_ant(sf::RenderTarget &target, const Ant &ant) -> void;

    auto render_food(sf::RenderTarget &target, const Food &food_l) -> void;
};

#endif // RENDERER
