#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include "core/ds.h"
#include "core/hash.h"
#include "core/input.h"
#include "core/log.h"
#include <string>

namespace tt
{
    class c_window
    {
    public:
        c_window(uint32_t x, uint32_t y, char const* Title);
        
        bool is_open() const;
        bool update();
        bool make_texture(std::string const& image_path);
        bool make_sprite(std::string const& image_path, float x, float y);
        bool add_drawable(std::shared_ptr<sf::Drawable> drawable);

    private:
        sf::RenderWindow m_window;
        c_fixed_vector<sf::Texture, 512> m_textures;
        c_fixed_vector<std::shared_ptr<sf::Drawable>, 1024> m_drawables;
        std::unordered_map<c_hash, uint32_t, s_hash_hasher> m_texture_map;
        c_input m_input;
    };
}