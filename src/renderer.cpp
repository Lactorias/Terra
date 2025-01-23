#include "../includes/renderer/renderer.hpp"
#include "../includes/renderer/texturemanager.hpp"
#include "raylib.h"
#include <iostream>
#include <vector>

void Renderer::render(Colony &colony, float &, World &world) {
    static float time_accumulator = 0.0f;
    time_accumulator += GetFrameTime();

    batch_ants(colony);
    batch_trails(colony);
    batch_food(world);

    if (time_accumulator >= 0.2f) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            std::cout << "hello";
            world.create_food(mousePos);
        }
        time_accumulator = 0.0f;
    }
}

void Renderer::draw_batches() {}

void Renderer::batch_ants(const Colony &colony) {
    float scale_factor = 0.03f;

    for (auto const &ant : colony.get_ants()) {
        Vector2 scale = {scale_factor, scale_factor};
        auto rotation_deg = ant.direction * (180.0f / PI);
        rotation_deg += 90.0f;
        DrawTextureEx(TextureManager::get_instance().get_texture("ant").value(),
                      ant.position, rotation_deg, scale.x, GREEN);
    }
}

void Renderer::batch_trails(Colony &colony) {
    trail_vertices.clear();

    for (auto &ant : colony.get_ants()) {
        for (auto &trail : ant.trails.get_buffer()) {
            if (ant.has_food) {
                trail.trail_type = Trail_Type::HOME;
            }

            Color trailColor =
                (trail.trail_type == Trail_Type::HOME) ? RED : BLUE;
            DrawPixel(trail.position.x, trail.position.y, trailColor);
        }
    }
}

void Renderer::batch_food(const World &world) {
    food_vertices.clear();

    float scale_factor = 0.03f;
    for (const auto &food : world.get_foods()) {
        Vector2 scale = {scale_factor, scale_factor};
        DrawTextureEx(
            TextureManager::get_instance().get_texture("food").value(),
            food.position, 0.0f, scale.x, GREEN);
    }
}
