#ifndef RENDERER
#define RENDERER

#include "../simulation/ant/trail.hpp"
#include "../simulation/world/colony.hpp"
#include "../simulation/world/world.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

class Renderer {
public:
    Renderer() {}

    auto render(sf::RenderTarget &target, Colony &colony, float &DT,
                World &world, sf::RenderWindow &window) -> void;

    auto batch_ants(const Colony &colony) -> void;

    auto batch_trails(const Colony &colony) -> void;

    auto batch_food(const World &world, sf::RenderTarget &target) -> void;

    auto draw_batches(sf::RenderTarget &target) -> void;

private:
    auto render_colony(sf::RenderTarget &target, const Colony &colony_circle)
        -> void;

    auto render_ant(sf::RenderTarget &target, const Ant &ant) -> void;

    auto render_food(sf::RenderTarget &target, const Food &food_l) -> void;

    auto render_trail(sf::RenderTarget &target, const Trail &trail) -> void;

private:
    sf::VertexArray ant_vertices;
    sf::VertexArray trail_vertices;
    sf::VertexArray food_vertices;
};

#endif // RENDERER
