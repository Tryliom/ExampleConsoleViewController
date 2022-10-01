#pragma once
#include <functional>

#include "../InteractiveObject.h"

namespace Console
{
	class Selector: public InteractiveObject
	{
	protected:
		std::vector<std::string> _options;
		int _selected{ 0 };
		std::function<void(int)> _setValue;
	public:
		Selector(std::function<int(Screen)> getX, std::function<int(Screen)> getY, const std::vector<std::string>& options, const std::function<void(int)>& setValue, bool xCentered = false);

		void Draw(Screen& screen, bool selected) override;
		void OnKeyPress(Controller* controller, const char key) override;
	};
}