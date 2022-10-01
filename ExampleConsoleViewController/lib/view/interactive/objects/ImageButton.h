#pragma once
#include "../InteractiveObject.h"

#include <functional>

namespace Console
{
	class ImageButton : public InteractiveObject
	{
	protected:
		Image _image;
		bool _yCentered{ false };
		std::function<void()> _onClick;
	public:
		ImageButton(std::function<int(Screen)> getX, std::function<int(Screen)> getY, const Image& image, const std::function<void()>& onClick, const bool xCentered = false, const bool yCentered = false,
					Background background = Background::NONE, Foreground foreground = Foreground::NONE);

		void Draw(Screen& screen, bool selected) override;
		void OnKeyPress(Controller* controller, const char key) override;
	};
}
