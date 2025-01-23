#ifndef COLONY
#define COLONY

#include "../ant/ant.hpp"
#include "raylib.h"
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

class AntState {
public:
    AntState() = default;
    AntState(const AntState &other) = delete;
    AntState(AntState &&other) = delete;

    auto add_ant(const Ant &ant) noexcept -> void {
        ants.push_back(ant);
        ant_mapping[ant.id] = &ants.back();
    }

    auto get_ant_id(int id) noexcept -> std::optional<Ant *> {
        if (ant_mapping.contains(id)) {
            return ant_mapping[id];
        }
        return std::nullopt;
    }

    auto get_ants() noexcept -> std::vector<Ant> & { return ants; }

    auto get_ants() const noexcept -> const std::vector<Ant> & { return ants; }

private:
    std::vector<Ant> ants;
    std::unordered_map<int, Ant *> ant_mapping;
};

class Colony {
public:
    Colony(float x, float y, int32_t num_ants)
        : position(x, y), num_ants(num_ants) {
        for (int32_t i = 0; i < num_ants; i++) {
            float rand_dir = static_cast<float>(
                static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2);
            ant_state->add_ant(Ant(x, y, rand_dir));
        }
    }

    auto get_ants() const -> const std::vector<Ant> &;

    auto get_ants() -> std::vector<Ant> &;

    auto get_pos() const -> const Vector2 &;

    auto get_state() const noexcept -> const std::unique_ptr<AntState> & {
        return ant_state;
    }

    auto update(float DT) -> void;

private:
    Vector2 position;
    const int32_t num_ants;
    std::unique_ptr<AntState> ant_state = std::make_unique<AntState>();
};

#endif // COLONY
