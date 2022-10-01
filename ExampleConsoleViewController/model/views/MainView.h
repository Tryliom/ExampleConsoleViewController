#pragma once
#include "../../lib/ConsoleViewController.h"

class MainView: public Console::View
{
public:
	MainView();

	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};

