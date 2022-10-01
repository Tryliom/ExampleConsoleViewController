#include "ShopView.h"
#include "../controller/MainController.h"

ShopView::ShopView()
{
	setComponents({
		new Console::BasicButton("Buy", GetMiddleScreen(), ReturnPosition(8), [this](Console::Controller* controller)
		{
			const auto mainController = dynamic_cast<MainController*>(controller);
			if (mainController->GetCostCps() <= mainController->GetClicks())
			{
				mainController->IncrementCps();
				mainController->UseClicks(mainController->GetCostCps());
				mainController->IncrementCost();
			}
			else
			{
				_errorMessage = "You don't have enough clicks to buy that !";
			}
		}, true, true)
		});
}

void ShopView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	const auto mainController = dynamic_cast<MainController*>(controller);

	screen.Draw(Console::Text{ .Str = "Shop", .X = screen.GetWidth() / 2, .Y = 2, .XCentered = true });
	screen.Draw(Console::Text{ .Str = std::to_string(mainController->GetClicks()) + " clicks", .X = screen.GetWidth() * 3 / 4, .Y = 2 });
	screen.Draw(Console::Text{ .Str = "Click per seconds: " + std::to_string(mainController->GetClickPerSecond()), .X = screen.GetWidth() / 4, .Y = 5});
	screen.Draw(Console::Text{ .Str = "Cost: " + std::to_string(mainController->GetCostCps()) + " clicks", .X = screen.GetWidth() * 3 / 4, .Y = 5});
	screen.Draw(Console::Text{ .Str = _errorMessage, .X = screen.GetWidth() / 2, .Y = 11, .XCentered = true, .Foreground = Console::Foreground::RED });

	screen.Draw(Console::Text{ .Str = "Exit: Back | Confirm: Enter", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() - 3, .XCentered = true });
}

void ShopView::OnKeyPressed(Console::Controller* controller, const char key)
{
	_errorMessage.clear();

	View::OnKeyPressed(controller, key);
}
