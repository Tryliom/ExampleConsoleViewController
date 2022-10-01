#include "Controller.h"
#include "../utilities/Utility.h"

#include <conio.h>
#include <thread>

namespace Console
{
	void Controller::GoBack()
	{
		this->_view = this->_views.top();
		this->_views.pop();
	}

	void Controller::ClearStack()
	{
		_views = std::stack<View*>();
	}

	void Controller::update()
	{
		// Update the view
		if (this->_view != nullptr)
		{
			this->_view->Update(this, this->_screen);
		}
	}

	void Controller::onKeyPressed(const char key)
	{
		// If the view is not null, call the view's onKeyPressed method
		if (this->_view != nullptr)
		{
			this->_view->OnKeyPressed(this, key);
		}

		// If the key is Escape, exit the program or go back to the last view
		if (key == Key::Escape)
		{
			if (_views.empty())
			{
				// Close the program
				this->_view = nullptr;
				Utility::sleep(300);
				exit(0);
			}

			GoBack();
		}
	}

	void Controller::refresh()
	{
		_screen.Reset();
		this->update();
		_screen.Render();
	}

	void Controller::startRenderingThread()
	{
		std::thread renderThread([this]()
			{
				auto nextFrame = std::chrono::steady_clock::now();

				while (true)
				{
					nextFrame += std::chrono::milliseconds(1000 / FPS);

					this->refresh();
					Tick++;

					if (LIMIT_FPS)
					{
						std::this_thread::sleep_until(nextFrame);
					}
				}
			}
		);
		renderThread.detach();

		std::thread fpsThread([this]()
			{
				while (true)
				{
					Utility::sleep(1000);
					this->CurrentFPS = Tick;
					Tick = 0;
				}
			}
		);
		fpsThread.detach();
	}

	void Controller::Start()
	{
		startRenderingThread();

		// Get every key pressed
		while (const char key = static_cast<char>(_getch()))
		{
			if (_canPressKey) {
				_canPressKey = false;
				this->onKeyPressed(key);
				_canPressKey = true;
			}
		}
	}

	void Controller::ChangeView(View* view)
	{
		if (this->_view != nullptr)
		{
			// Push the current view to the stack
			this->_views.push(this->_view);
		}

		// Set the new view as the current view
		this->_view = view;
	}
}

