#include "ImageButton.h"

namespace Console
{
	ImageButton::ImageButton(std::function<int(Screen)> getX, std::function<int(Screen)> getY, const Image& image, const std::function<void()>& onClick, const bool xCentered,
							const bool yCentered, const Background background, const Foreground foreground) :
		InteractiveObject(getX, getY, xCentered)
	{
		_image = image;
		_onClick = onClick;
		_yCentered = yCentered;
		_background = background;
		_foreground = foreground;
	}

	void ImageButton::Draw(Screen& screen, bool selected)
	{
		auto background = Background::NONE;
		auto foreground = Foreground::NONE;
		int y = _getY(screen);
		int x = _getX(screen);

		if (_yCentered)
		{
			y -= _image.GetHeight() / 2;
		}

		for (const std::string& row : _image.GetImage())
		{
			screen.Draw(Text{ .Str = row, .X = x, .Y = y, .XCentered = _xCentered, .Background = background, .Foreground = foreground });
		}
	}

	void ImageButton::OnKeyPress(Controller* controller, const char key)
	{
		if (key == Key::Enter)
		{
			_onClick();
		}
	}
}
