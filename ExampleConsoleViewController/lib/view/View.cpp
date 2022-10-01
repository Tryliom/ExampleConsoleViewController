#include "View.h"

namespace Console
{
	View::View(const int defaultButton)
	{
		_currentButton = defaultButton;
	}

	void View::Update(Controller* controller, Screen& screen)
	{
		for (const auto& component : _components)
		{
			component->Draw(screen, component == _components[_currentButton]);
		}
	}

	void View::OnKeyPressed(Controller* controller, const char key)
	{
		const int maxButtons = GetMaxButton();

		if (maxButtons == 0)
			return;

		if (_currentButton >= maxButtons)
		{
			_currentButton = maxButtons - 1;
		}
		if (_currentButton < 0)
		{
			_currentButton = 0;
		}

		if (_currentButton >= 0)
		{
			_components[_currentButton]->OnKeyPress(controller, key);
		}
	}
}