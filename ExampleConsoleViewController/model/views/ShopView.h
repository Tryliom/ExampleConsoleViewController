#pragma once
#include "../../lib/ConsoleViewController.h"

class ShopView: public Console::View
{
private:
	std::string _errorMessage;

public:
	ShopView();

	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

