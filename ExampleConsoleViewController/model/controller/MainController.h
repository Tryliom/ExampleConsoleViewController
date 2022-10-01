#pragma once
#include "../../lib/ConsoleViewController.h"

class MainController : public Console::Controller
{
private:
	int _clicks{0};
	int _clickPerSecond{ 0 };
	int _costCps{ 10 };

public:
	MainController();

	void IncrementClicks() { _clicks++; }
	void IncrementCps() { _clickPerSecond++; }
	void UseClicks(const int clicks) { _clicks -= clicks; }
	void IncrementCost() { _costCps += 5; }
	int GetClicks() const { return _clicks; }
	int GetClickPerSecond() const { return _clickPerSecond; }
	int GetCostCps() const { return _costCps; }
};

