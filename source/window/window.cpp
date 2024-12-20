#include "window.h"

namespace tt
{
    c_window::c_window(uint32_t x, uint32_t y, char const* title)
        : m_window(sf::VideoMode(x, y), title)
    {
    }

	c_window::c_window(uint32_t x, uint32_t y, std::string const& title)
		: m_window(sf::VideoMode(x, y), title.c_str())
	{
	}

	bool c_window::is_open() const
    { 
        return m_window.isOpen(); 
    }

    bool c_window::update()
    {
		if (!m_window.isOpen())
		{
			return false;
		}

        m_input.reset();
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
                return false;
            }
            else
            {
                m_input.on(event);
            }
        }

        m_window.clear(sf::Color::Black);
        for (const auto& drawable : m_drawables)
        {
            assert(drawable != nullptr);
            m_window.draw(*drawable);
        }
        m_window.display();
        return true;
    }

    bool c_window::make_texture(std::string const& image_path)
    {
        c_hash image_hash(image_path);
        try
        {
            if (m_texture_map.contains(image_hash))
            {
                return true;
            }

            if (!m_textures.emplace())
            {
                errorln("Failed to create texture for image: ", image_path);
                return false;
            }

            size_t texture_index = m_textures.count() - 1;
            sf::Texture& tex = m_textures[texture_index];

            if (!tex.loadFromFile(image_path))
            {
                errorln("Failed to load image from file: ", image_path);
                m_textures.remove_at_unordered(texture_index);
                return false;
            }

            m_texture_map[image_hash] = static_cast<uint32_t>(texture_index);
        }
        catch (const std::exception& e)
        {
            errorln("Exception occurred while creating texture: ", e.what());
            return false;
        }
        catch (...)
        {
            errorln("Unknown error occurred while creating texture for image: ", image_path);
            return false;
        }
        return true;
    }

    bool c_window::make_sprite(std::string const& image_path, float x, float y)
    {
        c_hash image_hash(image_path);
        try
        {
            std::shared_ptr<sf::Sprite> sprite;
            size_t texture_index;

            if (m_texture_map.contains(image_hash))
            {
                texture_index = m_texture_map[image_hash];
                sprite = std::make_shared<sf::Sprite>(m_textures[texture_index]);
            }
            else
            {
                if (!m_textures.emplace())
                {
                    errorln("Failed to create texture for image: ", image_path);
                    return false;
                }

                texture_index = m_textures.count() - 1;
                sf::Texture& tex = m_textures[texture_index];

                if (!tex.loadFromFile(image_path))
                {
                    errorln("Failed to load image from file: ", image_path);
                    m_textures.remove_at_unordered(texture_index);
                    return false;
                }

                sprite = std::make_shared<sf::Sprite>(tex);
                m_texture_map[image_hash] = static_cast<uint32_t>(texture_index);
            }

            sprite->setPosition(x, y);
            sprite->setScale(0.2f, 0.2f);

            if (!m_drawables.append(sprite))
            {
                errorln("Failed to append sprite to drawables");
                return false;
            }
        }
        catch (const std::exception& e)
        {
            errorln("Exception occurred while creating sprite: ", e.what());
            return false;
        }
        catch (...)
        {
            errorln("Unknown error occurred while creating sprite for image: ", image_path);
            return false;
        }
        return true;
    }

    bool c_window::add_drawable(std::shared_ptr<sf::Drawable> drawable)
    {
        return m_drawables.append(drawable);
    }
}