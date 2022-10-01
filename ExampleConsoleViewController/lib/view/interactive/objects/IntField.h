#pragma once
#include "BasicField.h"

namespace Console
{
	class IntField: public BasicField
	{
	protected:
		bool _enableLeftRightArrow{ true };

		std::string GetStr() const override;
		void onBackspace() override;
	public:
		IntField(std::function<int(Screen)> getX, std::function<int(Screen)> getY, const std::function<int()>& getValue, const std::function<void(int)>& setValue, bool xCentered = false, bool enableLeftRightArrow = true);

		void OnKeyPress(Controller* controller, char key) override;
	};
}
