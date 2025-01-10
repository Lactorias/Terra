#include "../includes/renderer/renderer.hpp"
#include "../includes/simulation/ant/ant.hpp"
#include "../includes/simulation/world/colony.hpp"
#include "../includes/simulation/world/world.hpp"
#include <SFML/Graphics.hpp>
#include <benchmark/benchmark.h>

void runSimulationStep(sf::RenderWindow &window, Colony &colony,
                       Renderer &renderer, World &world, float dt) {
    colony.update(dt); // Update the colony state
    window.clear();    // Clear the screen
    renderer.render(window, colony, dt, world, window); // Render the simulation
    window.display(); // Display the rendered frame
}

static void BM_SimulationStep(benchmark::State &state) {
    // Initialize SFML and other components
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::RenderWindow window(sf::VideoMode(2000, 800), "Benchmark Window",
                            sf::Style::Default, settings);

    Colony colony(100, 100, 300);
    World world;
    Renderer renderer;

    sf::Clock clock;
    window.setFramerateLimit(144);

    while (state.KeepRunning()) {
        float dt = clock.restart().asSeconds();
        runSimulationStep(window, colony, renderer, world, dt);
    }

    window.close(); // Ensure window closes after benchmark
}

BENCHMARK(BM_SimulationStep);
BENCHMARK_MAIN();
