#include "MainView.h"

#include "ShopView.h"
#include "../controller/MainController.h"

MainView::MainView()
{
	setComponents({
		new Console::BasicButton("Gain clicks", GetMiddleScreen(), ReturnPosition(8), [this](Console::Controller* controller)
		{
			const auto mainController = dynamic_cast<MainController*>(controller);
			mainController->IncrementClicks();
		}, true, true),
		new Console::BasicButton("Shop", GetMiddleScreen(), ReturnPosition(12), [this](Console::Controller* controller)
		{
			const auto mainController = dynamic_cast<MainController*>(controller);
			mainController->ChangeView(new ShopView());
		}, true, true)
	});
}

void MainView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	const auto mainController = dynamic_cast<MainController*>(controller);

	screen.Draw(Console::Text{ .Str = "Clicker", .X = screen.GetWidth() / 2, .Y = 2, .XCentered = true });
	screen.Draw(Console::Text{ .Str = std::to_string(mainController->GetClicks()) + " clicks", .X = screen.GetWidth() / 2, .Y = 5, .XCentered = true });

	screen.Draw(Console::Text{ .Str = "Exit: Esc | Arrows: move | Confirm: Enter", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() - 3, .XCentered = true });
}

void MainView::OnKeyPressed(Console::Controller* controller, const char key)
{
	if (key == Console::Key::Down)
	{
		IncrementCurrentButton();
	}
	else if (key == Console::Key::Up)
	{
		DecrementCurrentButton();
	}

	View::OnKeyPressed(controller, key);
}
