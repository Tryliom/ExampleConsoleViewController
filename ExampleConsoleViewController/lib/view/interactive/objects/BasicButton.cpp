#include "BasicButton.h"

namespace Console
{
	BasicButton::BasicButton(const std::string& str, const std::function<int(Screen)> getX, const std::function<int(Screen)> getY, const std::function<void(Controller* controller)>& onClick, const bool xCentered, const bool yCentered) :
		InteractiveObject(getX, getY, xCentered)
	{
		_str = str;
		_yCentered = yCentered;
		_onClick = onClick;
	}

	void BasicButton::Draw(Screen& screen, const bool selected)
	{
		auto background = _background;
		auto foreground = _foreground;
		int y = _getY(screen);
		int x = _getX(screen);

		if (selected)
		{
			background = _selectedBackground;
			foreground = _selectedForeground;
		}

		if (_yCentered)
		{
			y -= 1;
		}

		// Draw a border around the button
		std::string border;
		for (int i = 0; i < static_cast<int>(_str.length()) + 2; i++)
		{
			border += _rowBorder;
		}

		std::string text = _columnBorder + _str + _columnBorder;

		screen.Draw(Text{ .Str = border, .X = x, .Y = y, .XCentered = _xCentered, .Background = background, .Foreground = foreground });
		screen.Draw(Text{ .Str = text, .X = x, .Y = y + 1, .XCentered = _xCentered, .Background = background, .Foreground = foreground });
		screen.Draw(Text{ .Str = border, .X = x, .Y = y + 2, .XCentered = _xCentered, .Background = background, .Foreground = foreground });
	}

	void BasicButton::OnKeyPress(Controller* controller, const char key)
	{
		if (key == Key::Enter)
		{
			_onClick(controller);
		}
	}
}