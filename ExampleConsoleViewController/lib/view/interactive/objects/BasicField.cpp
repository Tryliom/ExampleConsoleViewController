#include "BasicField.h"

Console::BasicField::BasicField(const std::function<int(Screen)> getX, const std::function<int(Screen)> getY, const std::function<std::string()>& getValue,
                                const std::function<void(std::string)>& setValue, const std::function<bool(char key)>& condition, const bool xCentered, const bool showCursor) :
	InteractiveObject(getX, getY, xCentered)
{
	_getValue = getValue;
	_setValue = setValue;
	_condition = condition;
	_str = _getValue();
	_showCursor = showCursor;
}

void Console::BasicField::Draw(Screen& screen, const bool selected)
{
	auto background = _background;
	auto foreground = _foreground;
	int x = _getX(screen);
	int y = _getY(screen);

	if (selected)
	{
		background = _selectedBackground;
		foreground = _selectedForeground;
	}

	screen.Draw(Text{ .Str = GetStr(), .X = x, .Y = y, .XCentered = _xCentered, .Background = background, .Foreground = foreground });

	if (_showCursor)
	{
		screen.SetCursor(x + static_cast<int>(GetStr().length()), y);
	}
}

void Console::BasicField::OnKeyPress(Controller* controller, const char key)
{
	if (_condition(key))
	{
		onConditionValidation(key);
	}
	else if (key == Key::Backspace)
	{
		onBackspace();
	}
}

std::string Console::BasicField::GetStr() const
{
	return _str;
}

void Console::BasicField::onConditionValidation(const char key)
{
	_str += key;
	_setValue(_str);
}

void Console::BasicField::onBackspace()
{
	if (_str.length() > 0)
	{
		_str.pop_back();
		_setValue(_str);
	}
}
