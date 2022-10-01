#include "Image.h"

#include <fstream>
#include <iostream>

namespace Console
{
	Image::Image(const std::string& path)
	{
		_image = {};
		std::ifstream file(path);
		std::string line;

		while (std::getline(file, line))
		{
			_image.emplace_back(line);
		}

		_width = static_cast<int>(_image[0].length());
		_height = static_cast<int>(_image.size());
	}

	void Image::Reverse()
	{
		for (std::string& line: _image)
		{
			std::reverse(line.begin(), line.end());

			for (char& c : line)
			{
				if (REVERSE_CHARS.contains(c))
				{
					c = REVERSE_CHARS[c];
				}
			}
		}
	}

}