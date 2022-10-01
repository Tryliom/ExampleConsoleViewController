#include "MainController.h"

#include <thread>

#include "../views/MainView.h"

MainController::MainController()
{
	std::thread click([&]()
		{
			while (true)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				_clicks += _clickPerSecond;
			}
		}
	);
	click.detach();
	ChangeView(new MainView());
}
