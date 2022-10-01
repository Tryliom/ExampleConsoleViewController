#pragma once
#include "Image.h"
#include "../Constants.h"

#include <string>
#include <vector>

namespace Console
{
	// If true, a border will be drawn around the screen
	bool constexpr BORDER = true;
	// The character used to draw the columns for the border
	std::string const BORDER_COLUMN = "|";
	// The character used to draw the rows for the border
	std::string const BORDER_ROW = "=";

	struct Text
	{
		std::string Str{};
		int X{ 0 };
		int Y{ 0 };
		bool XCentered{ false };
		Background Background{ Background::NONE };
		Foreground Foreground{ Foreground::NONE };
	};

	class Screen
	{
	private:
		std::vector<std::vector<std::string>> _screen;
		// The cache of the previous screen
		std::vector<std::vector<std::string>> _cache;
		int _height;
		int _width;
		// The cursor position on the screen if it is displayed
		int _cursorX;
		int _cursorY;

		static void setPos(int x, int y);
	public:
		Screen();

		int GetHeight() const { return this->_height; }
		int GetWidth() const { return this->_width; }

		/**
		 * \brief Clear the screen and prepare it for a new display
		 */
		void Reset();
		/**
		 * \brief Render the screen
		 */
		void Render() const;
		/**
		 * \brief Draw a text on the screen
		 * \param text The text to draw
		 */
		void Draw(Text text);
		/**
		 * \brief Set windows size
		 * \param width The width of the window as pixel
		 * \param height The height of the window as pixel
		 */
		static void SetWindowSize(int width, int height);
		/**
		 * \brief Rename the window
		 * \param title The new title of the window
		 */
		static void SetTitle(const std::string& title);
		/**
		 * \brief Center the window on the screen
		 */
		static void CenterWindow();
		/**
		 * \brief Set the cursor position for this frame
		 * \param x The x position of the cursor
		 * \param y The y position of the cursor
		 */
		void SetCursor(const int x, const int y) { this->_cursorX = x; this->_cursorY = y; }
	};
}

