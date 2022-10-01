#pragma once
#include <functional>

#include "../Screen.h"
#include "../../Constants.h"
#include "../../controller/Controller.h"

namespace Console
{
	class Controller;

	class InteractiveObject
	{
	protected:
		std::function<int(Screen)> _getX;
		std::function<int(Screen)> _getY;
		bool _xCentered{ false };
		Background _background{ Background::NONE };
		Foreground _foreground{ Foreground::NONE };
		Background _selectedBackground{ Background::CYAN };
		Foreground _selectedForeground{ Foreground::BLACK };

	public:
		InteractiveObject(std::function<int(Screen)> getX, std::function<int(Screen)> getY, bool xCentered = false);

		virtual void Draw(Screen& screen, bool selected) = 0;
		virtual void OnKeyPress(Controller* controller, const char key) = 0;
	};


}


