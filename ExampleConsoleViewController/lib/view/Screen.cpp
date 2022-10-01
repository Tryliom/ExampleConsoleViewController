#include "screen.h"

#include <iostream>
#include <thread>
#include <windows.h>

namespace Console
{
	void setCursorVisibility(const bool visibility)
	{
		const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(output, &cursorInfo);
		cursorInfo.bVisible = visibility;
		SetConsoleCursorInfo(output, &cursorInfo);
	}

	void Screen::setPos(const int x, const int y)
	{
		// Set the position of the cursor
		COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
		const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
	}

	Screen::Screen()
	{
		this->_height = 0;
		this->_width = 0;
		this->_screen = {};
		this->_cache = {};
	}

	void Screen::Reset()
	{
		// Set the height and width according to the console window
		const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(output, &csbi);
		this->_height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		this->_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		this->_cache = this->_screen;
		this->_screen = {};

		// Hide the cursor
		setCursorVisibility(false);

		// Fill the screen with spaces and # if BORDER is true for borders
		for (int h = 0; h < _height; h++)
		{
			std::vector<std::string> row;
			for (int w = 0; w < _width; w++)
			{
				if (BORDER)
				{
					if (h == 0 || h == _height - 1)
					{
						row.emplace_back(BORDER_ROW);
					}
					else if (w == 0 || w == _width - 1)
					{
						row.emplace_back(BORDER_COLUMN);
					}
					else
					{
						row.emplace_back(" ");
					}
				}
				else
				{
					row.emplace_back(" ");
				}
			}

			this->_screen.emplace_back(row);
		}

		// Reset cursor position
		_cursorX = -1;
		_cursorY = -1;
	}

	void Screen::Render() const
	{
		// Display every lines of the screen
		for (int h = 0; h < _height; h++)
		{
			for (int w = 0; w < _width; w++)
			{
				// If the cache has a different size than the screen, display the whole screen, otherwise only the differences between the cache and the screen
				if (static_cast<int>(this->_cache.size()) != _height || static_cast<int>(this->_cache[h].size()) != _width || this->_cache[h][w] != _screen[h][w])
				{
					this->setPos(w, h);
					std::cout << _screen[h][w];
				}
			}
		}

		if (_cursorX != -1 && _cursorY != -1)
		{
			// Show the cursor
			setCursorVisibility(true);
			this->setPos(_cursorX, _cursorY);
		}
	}

	void Screen::Draw(Text text)
	{
		if (text.XCentered)
		{
			text.X -= static_cast<int>(text.Str.length()) / 2;
		}

		// If the text is out of the screen, don't draw it
		if (_height <= text.Y || _width <= text.X)
		{
			return;
		}

		// Colorize the Str if a background or foreground color is specified
		std::string preColor, postColor;

		if (text.Background != Background::NONE || text.Foreground != Foreground::NONE)
		{
			std::string colors;
			preColor = "\033[";
			postColor = "\033[0m";

			if (text.Background != Background::NONE)
			{
				colors += std::to_string(static_cast<int>(text.Background));
			}
			if (text.Foreground != Foreground::NONE)
			{
				if (!colors.empty())
				{
					colors += ";";
				}
				colors += std::to_string(static_cast<int>(text.Foreground));
			}

			preColor += colors + "m";
		}

		for (int i = 0; i < static_cast<int>(text.Str.size()); i++)
		{
			// Break if the text is out of the screen
			if (text.X + i >= _width)
			{
				break;
			}
			// Draw the character at the specified position with the specified color if any
			this->_screen[text.Y][text.X + i] = preColor + text.Str[i] + postColor;
		}
	}

	void Screen::SetWindowSize(const int width, const int height)
	{
		const HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r);
		MoveWindow(console, r.left, r.top, width, height, TRUE);
	}

	void Screen::SetTitle(const std::string& title)
	{
		SetConsoleTitleA(title.c_str());
	}

	void Screen::CenterWindow()
	{
		const HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r);
		const int width = r.right - r.left;
		const int height = r.bottom - r.top;
		const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		MoveWindow(console, (screenWidth - width) / 2, (screenHeight - height) / 2, width, height, TRUE);
	}
}
