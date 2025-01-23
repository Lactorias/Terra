#ifndef WORLD
#define WORLD

#include "colony.hpp"
#include "food.hpp"
#include "raylib.h"
#include <vector>

class FoodState {
public:
    FoodState() = default;
    FoodState(const FoodState &other) = delete;
    FoodState(FoodState &&other) = delete;

    auto add_food(const Food &food) noexcept -> void {
        foods.push_back(food);
        food_mappings[food.id] = &foods.back();
    }

    auto remove_food(int id) -> void {
        if (food_mappings.contains(id))
            food_mappings.erase(id);
    }

    auto get_foods() const noexcept -> const std::vector<Food> & {
        return foods;
    }

    auto get_foods() noexcept -> std::vector<Food> & { return foods; }

    auto get_food_id(int id) noexcept -> std::optional<Food *> {
        if (food_mappings.contains(id)) {
            return std::make_optional(food_mappings[id]);
        }
        return std::nullopt;
    }

private:
    std::vector<Food> foods;
    std::unordered_map<int, Food *> food_mappings;
};

class World {
public:
    World() {}

    void create_food(const Vector2 &mouse_position) {
        food_state->add_food(Food(mouse_position));
    }

    auto remove_food(int id) -> void {
        if (food_state) {
            food_state->remove_food(id);
        }
    }

    auto get_foods() const noexcept -> const std::vector<Food> & {
        return food_state->get_foods();
    }
    auto get_foods() noexcept -> std::vector<Food> & {
        return food_state->get_foods();
    }

    auto get_state() noexcept -> std::unique_ptr<FoodState> & {
        return food_state;
    }
    auto get_state() const noexcept -> const std::unique_ptr<FoodState> & {
        return food_state;
    }

private:
    std::unique_ptr<FoodState> food_state = std::make_unique<FoodState>();
};

#endif // WORLD
