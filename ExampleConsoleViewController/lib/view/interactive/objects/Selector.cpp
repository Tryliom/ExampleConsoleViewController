#include "Selector.h"

namespace Console
{
	Selector::Selector(const std::function<int(Screen)> getX, const std::function<int(Screen)> getY, const std::vector<std::string>& options,
	                   const std::function<void(int)>& setValue, const bool xCentered) :
		InteractiveObject(getX, getY, xCentered)
	{
		_options = options;
		_setValue = setValue;
	}

	void Selector::Draw(Screen& screen, const bool selected)
	{
		Background background = _background;
		Foreground foreground = _foreground;

		if (selected)
		{
			background = _selectedBackground;
			foreground = _selectedForeground;
		}

		int x = _getX(screen);
		int y = _getY(screen);
		for (int i = 0; i < static_cast<int>(_options.size()); i++)
		{
			if (i == _selected)
			{
				if (!selected)
				{
					background = Background::WHITE;
					foreground = Foreground::BLACK;
				}
				screen.Draw(Text{ .Str = "<" + _options[i] + ">", .X = x, .Y = y, .XCentered = false, .Background = background, .Foreground = foreground});
			}
			else
			{
				screen.Draw(Text{ .Str = _options[i], .X = x, .Y = y, .XCentered = false, .Background = _background, .Foreground = _foreground });
			}
			
			x += static_cast<int>(_options[i].length()) + 4;
		}
	}

	void Selector::OnKeyPress(Controller* controller, const char key)
	{
		if (key == Key::Left)
		{
			_selected--;
		}
		else if (key == Key::Right)
		{
			_selected++;
		}

		if (_selected >= static_cast<int>(_options.size()))
		{
			_selected = static_cast<int>(_options.size()) - 1;
		}
		else if (_selected < 0)
		{
			_selected = 0;
		}

		_setValue(_selected);
	}
}
