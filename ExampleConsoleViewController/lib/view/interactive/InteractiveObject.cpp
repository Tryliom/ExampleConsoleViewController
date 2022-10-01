#include "InteractiveObject.h"

namespace Console {
	InteractiveObject::InteractiveObject(const std::function<int(Screen)> getX, const std::function<int(Screen)> getY, const bool xCentered)
	{
		_getX = getX;
		_getY = getY;
		_xCentered = xCentered;
	}
}
