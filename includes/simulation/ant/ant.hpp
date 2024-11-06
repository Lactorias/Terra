#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

#pragma once

class Ant {
public:
    Ant(float x, float y, float angle)
        : position(x, y), direction(angle), direction_time_elapsed(0.0f) {}

    void update(const float DT) {
        update_position(DT);

        direction = lerp_angle(direction, target_direction, turn_speed * DT);

        direction_time_elapsed += DT;

        if (direction_time_elapsed >= direction_time_period) {
            new_direction();
        }
    }

    void update_position(const float DT) {
        constexpr float speed = 200.0f;

        position += (DT * speed) * sf::Vector2f(cos(direction), sin(direction));

        check_boundaries();
    }

    void check_boundaries() {
        if (position.x < 0.0f) {
            position.x = 0.0f;
            direction = PI - direction;
        } else if (position.x > map_width) {
            position.x = map_width;
            direction = PI - direction;
        }

        if (position.y < 0.0f) {
            position.y = 0.0f;
            direction = -direction;
        } else if (position.y > map_height) {
            position.y = map_height;
            direction = -direction;
        }

        direction = std::fmod(direction + 2.0f * PI, 2.0f * PI);
    }

    void new_direction() {
        float new_angle = 0.0f;

        const float max_range = PI;
        const float min_range = PI * 0.2f;

        float range = (rand() % 2 == 0) ? max_range : min_range;

        target_direction = direction + get_rand_range(range);

        target_direction = std::fmod(target_direction + 2.0f * PI, 2.0f * PI);

        turn_speed = 2.0f + static_cast<float>(rand() % 100) / 100.0f * 2.0f;

        direction_time_elapsed = 0.0f;
    }

	float get_rand_range(float width) {
        constexpr int32_t max_val = 10000;
        constexpr int32_t half = max_val / 2;
        constexpr float div = 1.0f / float(max_val);
        const float val = (rand() % max_val - half) * div * width;
        return val;
    }

    void render(sf::RenderTarget &target) {
        const float width = 2.0f;
        const float length = 7.0f;
        sf::RectangleShape body(sf::Vector2f(width, length));
        body.setOrigin(width * 0.5f, length * 0.5f);
        body.setPosition(position);
        body.setRotation(direction * 57.2958f + 90.0f);
        body.setFillColor(sf::Color::Green);
        target.draw(body);
    }

    sf::Vector2f position;
    float direction;
    float target_direction;
    float direction_time_elapsed;
    constexpr static float direction_time_period = 0.5f;
    constexpr static float PI = 3.14159265f;
    const int32_t map_height = 800;
    const int32_t map_width = 800;
    float turn_speed = 3.0f;

    float lerp_angle(float start, float end, float t) {
        float difference = std::fmod(end - start + PI, 2.0f * PI) - PI;
        return start + difference * t;
    }
};
