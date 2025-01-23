#include "../includes/simulation/ant/ant.hpp"
#include "../includes/simulation/world/colony.hpp"
#include "../includes/simulation/world/qtree.hpp"
#include "raylib.h"
#include <benchmark/benchmark.h>

static void BM_SimulationStep(benchmark::State &state) {
    // Initialize SFML and other components
    //                        sf::Style::Default, settings);
    //
    InitWindow(800, 800, "Ant Simulator - Terra");
    Texture2D ant_texture = LoadTexture("../build/ant.png");
    auto const window_width = 800;

    SetTargetFPS(144);
    auto const square_width = window_width / 2;
    TextureManager::get_instance().load_textures();

    World world;
    Colony colony(100, 100, 300);
    // World world;
    //  Renderer renderer;

    while (state.KeepRunning()) {
        float dt = GetFrameTime();
        colony.update(dt); // Update the colony state
        BeginDrawing();
        ClearBackground(BLACK);
        QTree qtree =
            QTree(0, 0, static_cast<float>(square_width * 2),
                  static_cast<float>(square_width * 2), 0, 8, world, colony);

        qtree.collect_entities(qtree.ants_contained, colony.get_ants());

        qtree.observe();

        qtree.search_tiles();
        qtree.draw_q();

        float scale_factor = 0.03f;

        for (auto const &ant : colony.get_ants()) {
            Vector2 scale = {scale_factor, scale_factor};
            auto rotation_deg = ant.direction * (180.0f / PI);
            rotation_deg += 90.0f;
            DrawTextureEx(ant_texture, ant.position, rotation_deg, scale.x,
                          GREEN);
        }

        EndDrawing();
    }
    UnloadTexture(ant_texture);
    TextureManager::get_instance().unload_textures();
    CloseWindow();
}

BENCHMARK(BM_SimulationStep);
BENCHMARK_MAIN();
