#pragma once
#include "../InteractiveObject.h"

#include <functional>

namespace Console
{
	class BasicButton : public InteractiveObject
	{
	protected:
		std::string _str{};
		bool _yCentered{ false };
		std::function<void(Controller* controller)> _onClick{};
		std::string _rowBorder{ "-" };
		std::string _columnBorder{ "|" };

	public:
		BasicButton(const std::string& str, std::function<int(Screen)> getX, std::function<int(Screen)> getY, const std::function<void(Controller* controller)>& onClick, bool xCentered = false, bool yCentered = false);
		
		void Draw(Screen& screen, bool selected) override;
		void OnKeyPress(Controller* controller, char key) override;
	};
}

