#ifndef RENDERER
#define RENDERER

#include "../simulation/ant/trail.hpp"
#include "../simulation/world/colony.hpp"
#include "../simulation/world/world.hpp"
#include "raylib.h"
#include <unordered_map>

class Renderer {
public:
    Renderer() {}

    auto render(Colony &colony, float &DT, World &world) -> void;

    auto batch_ants(const Colony &colony) -> void;

    auto batch_trails(Colony &colony) -> void;

    auto batch_food(const World &world) -> void;

    auto draw_batches() -> void;

private:
    auto render_colony(const Colony &colony_circle) -> void;

    auto render_ant(const Ant &ant) -> void;

    auto render_food(const Food &food_l) -> void;

    auto render_trail(const Trail &trail) -> void;

private:
    std::vector<Vector2> ant_vertices;
    std::vector<Vector2> trail_vertices;
    std::vector<Vector2> food_vertices;
};

#endif // RENDERER

