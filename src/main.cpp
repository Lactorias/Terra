#include "../includes/renderer/renderer.hpp"
#include "../includes/renderer/texturemanager.hpp"
#include "../includes/simulation/ant/ant.hpp"
#include "../includes/simulation/world/colony.hpp"
#include "../includes/simulation/world/qtree.hpp"
#include "../includes/simulation/world/world.hpp"
#include "raylib.h"
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    auto const window_height = 800;
    auto const window_width = 800;

    InitWindow(window_width, window_height, "Ant Simulator - Terra");

    Texture2D ant_texture = LoadTexture("../build/ant.png");

    TextureManager::get_instance().load_textures();

    Colony colony(100, 100, 30);

    SetTargetFPS(144);

    Renderer renderer;

    auto const square_width = window_width / 2;

    World world;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        colony.update(dt);

        BeginDrawing();
        ClearBackground(BLACK);
        renderer.render(colony, dt, world);
        QTree qtree =
            QTree(0, 0, static_cast<float>(square_width * 2),
                  static_cast<float>(square_width * 2), 0, 8, world, colony);

        qtree.collect_entities(qtree.ants_contained, colony.get_ants());

        qtree.collect_entities_s(qtree.foods_contained, world.get_foods());

        qtree.observe();

        qtree.search_tiles();
        qtree.draw_q();

        EndDrawing();
    }
    UnloadTexture(ant_texture);

    TextureManager::get_instance().unload_textures();
    CloseWindow();
}
