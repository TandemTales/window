#include "window/window_manager.h"
#include "factory/factory.h"
#include <cassert>

using namespace tt;

int main()
{
	c_factory factory;
	factory.register_manager<c_window_manager>();
	factory.load("data/data.json");
	factory.create();
	c_window_manager* window_manager = factory.get_manager<c_window_manager>();
	assert(window_manager != nullptr);
	while (window_manager->update());
	return 0;
}
