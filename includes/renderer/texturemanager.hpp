#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER

#include "raylib.h"
#include <optional>
#include <string>
#include <unordered_map>

class TextureManager {
public:
    static auto get_instance() -> TextureManager & {
        static TextureManager instance;
        return instance;
    }

    auto load_textures() -> void {
        square_texture = LoadTexture("../build/pngegg.png");
        ant_texture = LoadTexture("../build/ant.png");
        food_texture = LoadTexture("../build/food.png");

        textures["ant"] = ant_texture;
        textures["food"] = food_texture;
        textures["square"] = square_texture;
    }

    auto unload_textures() -> void {
        UnloadTexture(square_texture);
        UnloadTexture(food_texture);
        UnloadTexture(ant_texture);
    }

    auto get_texture(const std::string &input) const
        -> const std::optional<Texture2D> {
        if (textures.contains(std::move(input))) {
            return std::make_optional(textures.at(input));
        }
        return std::nullopt;
    }

private:
    TextureManager() = default;
    ~TextureManager() = default;

    Texture2D square_texture;
    Texture2D ant_texture;
    Texture2D food_texture;

    std::unordered_map<std::string, Texture2D> textures;
};

#endif // TEXTUREMANAGER
