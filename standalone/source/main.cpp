#include "window/window.h"

using namespace tt;

int main()
{
	c_window window(500, 500, "Tandem Tales");
	while (window.update());
	return 0;
}
