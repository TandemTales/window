#include "window_manager.h"

namespace tt
{
	c_window_manager::~c_window_manager()
	{
		for (auto& window : m_windows)
		{
			delete window.second;
		}

		m_windows.clear();
	}

	void c_window_manager::create_instance(c_hash name, c_json& data)
	{
		// Create window
		uint32_t width = data["width"].is_number_unsigned() ? data["width"].get<uint32_t>() : default_width;
		uint32_t height = data["height"].is_number_unsigned() ? data["height"].get<uint32_t>() : default_height;
		std::string title = data["title"].is_string() ? data["title"].get<std::string>() : default_title;
		c_window* window = new c_window(width, height, title);
		m_windows[name] = window;
	}

	c_window* c_window_manager::get_window(c_hash name) const
	{
		auto it = m_windows.find(name);
		if (it != m_windows.end())
		{
			return it->second;
		}
		return nullptr;
	}

	bool c_window_manager::update()
	{
		bool keep_going = false;
		for (auto& window : m_windows)
		{
			if (window.second->update())
			{
				keep_going = true;
			}
		}
		return keep_going;
	}
}
