#pragma once
#include <map>
#include <string>
#include <vector>

inline std::map<char, char> REVERSE_CHARS = {
	{'/', '\\'},
	{'\\', '/'},
	{'{', '}'},
	{'}', '{'},
	{'(', ')'},
	{')', '('},
	{'[', ']'},
	{']', '['},
	{'<', '>'},
	{'>', '<'}
};

namespace Console
{
	class Image
	{
	private:
		std::vector<std::string> _image;
		int _width{ 0 };
		int _height{ 0 };

	public:
		Image() = default;
		explicit Image(const std::string& path);

		std::vector<std::string> GetImage() const { return this->_image; }
		int GetWidth() const { return this->_width; }
		int GetHeight() const { return this->_height; }

		void Reverse();
	};
}
