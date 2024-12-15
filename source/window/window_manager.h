#pragma once

#include "window.h"
#include "factory/manager.h"
#include "core/hash.h"

namespace tt
{
	class c_window_manager : public c_manager
	{
	public:
		static constexpr c_hash manager_type = "window"_h;
		static constexpr uint32_t default_width = 800;
		static constexpr uint32_t default_height = 600;
		static constexpr char const* default_title = "Window";

	public:
		virtual ~c_window_manager();
		void create_instance(c_hash name, c_json& data) override;
		c_window* get_window(c_hash name) const;
		c_hash get_type() const override { return manager_type; }
		bool update();

	private:
		std::unordered_map<c_hash, c_window*, s_hash_hasher> m_windows;
	};
}