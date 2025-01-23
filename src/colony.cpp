#include "../includes/simulation/world/colony.hpp"

auto Colony::get_ants() const -> const std::vector<Ant> & {
    return ant_state->get_ants();
}

auto Colony::get_ants() -> std::vector<Ant> & { return ant_state->get_ants(); }

auto Colony::get_pos() const -> const Vector2 & { return position; }

auto Colony::update(float DT) -> void {
    for (auto &ant : ant_state->get_ants()) {
        ant.update(DT);
    }
}
