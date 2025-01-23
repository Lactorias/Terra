#include "../includes/simulation/world/qtree.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
using std::find;

// Recursively check tiles, call search tiles on children
void QTree::search_tiles() {
    // Run ant against all other food, only in this region, O(nlogn)!
    for (auto &ant : ants_contained) {
        for (auto &food : foods_contained) {
            auto &ele = *m_world.get_state()->get_food_id(food).value();
            if (entity_collison(ant, ele)) {
                grab_food(ant, ele);
            }
        }
        /*
for (auto &trail : trails_contained) {
    if (ant.dropping_trail != trail.trail_type &&
        entity_collison_p(ant, trail)) {
        follow_trail(ant, trail);
    }
}
        */
    }

    for (auto const &child : children) {
        if (child) {
            child->search_tiles();
        }
    }
}

void QTree::subdivide() {
    if (children[0] != nullptr)
        return;
    if (level == max_level) {
        return;
    }
    level++;
    auto child_width = width / 2.0f;
    children[0] =
        std::make_unique<QTree>(x, y, child_width, child_width, level + 1,
                                max_level, m_world, m_colony);
    children[1] =
        std::make_unique<QTree>(x + child_width, y, child_width, child_width,
                                level + 1, max_level, m_world, m_colony);
    children[2] =
        std::make_unique<QTree>(x, y + child_width, child_width, child_width,
                                level + 1, max_level, m_world, m_colony);
    children[3] = std::make_unique<QTree>(x + child_width, y + child_width,
                                          child_width, child_width, level + 1,
                                          max_level, m_world, m_colony);

    for (const auto &ant : ants_contained) {
        for (size_t i = 0; i < 4; ++i) {
            if (within_tile(ant, children[i]->tile)) {
                children[i]->ants_contained.push_back(ant);
                break;
            }
        }
    }

    for (const auto &food : foods_contained) {
        for (size_t i = 0; i < 4; ++i) {
            if (within_tile(*m_world.get_state()->get_food_id(food).value(),
                            children[i]->tile)) {
                children[i]->foods_contained.insert(food);
                break;
            }
        }
    }

    for (const auto &trail : trails_contained) {
        for (size_t i = 0; i < 4; ++i) {
            if (within_tile(trail, children[i]->tile)) {
                children[i]->trails_contained.push_back(trail);
                break;
            }
        }
    }

    ants_contained.clear();
    foods_contained.clear();
    trails_contained.clear();
}

void QTree::observe() {
    if (children[0] == nullptr && (std::ssize(ants_contained) >= capacity ||
                                   std::ssize(foods_contained) >= capacity)) {
        subdivide();
    }
    if (children[0] != nullptr) {
        for (auto const &child : children) {
            child->observe();
        }
    }
}

void QTree::grab_food(Ant &ant, const Food &food) {

    auto it_ant = m_colony.get_state()->get_ant_id(ant.id).value();

    if (!it_ant->has_food) {
        it_ant->has_food = true;

        auto it = m_world.get_state()->get_food_id(food.id).value();
        foods_contained.contains(it->id);
        // if (foods_contained.contains(food.id)) {
        //    foods_contained.erase(food.id);
        // }
        if (m_world.get_state() != nullptr) {
            std::cout << "NULLLLLLLLLLLLLLLL" << '\n';
        }
        m_world.remove_food(it->id);
    }
}

void QTree::collect_trails() {
    for (auto const &ant : ants_contained) {
        for (size_t i = 0; i < 100; ++i) {
            auto &trails = ant.trails.get_buffer();
            if (within_tile(trails[i], this->tile))
                this->trails_contained.emplace_back(trails[i]);
        }
    }
}

void QTree::follow_trail(Ant &antt, const Trail &trail) {
    /*
auto ant = find(begin(m_colony.get_ants()), end(m_colony.get_ants()), antt);
Vector2 direction_trail = {trail.get_pos().x - ant->position.x,
                           trail.get_pos().y - ant->position.y};
float length = sqrtf(direction_trail.x * direction_trail.x +
                     direction_trail.y * direction_trail.y);
direction_trail.x /= length;
direction_trail.y /= length;
ant->target_direction = atan2f(direction_trail.y, direction_trail.x);
    */
}
