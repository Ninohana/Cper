#include "keymap.hpp"
#include "keycode.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

std::map<std::string, CKey> keyMap;

std::vector<std::string> split_string(const std::string& str, char delimiter) {
	std::istringstream iss(str);
	std::vector<std::string> tokens;
	std::string token;
	while (std::getline(iss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void getKeyMap(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "无法打开文件：" << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (std::getline(file, line))
	{
		if ('#' == line[0])
			continue;// 注释，跳过该行

		// 键=值，提取'='两边
		size_t pos = line.find_first_of('=');
		if (pos != std::string::npos)
		{
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1);
			// 删首尾空
			key.erase(0, key.find_first_not_of("\t\n\r\f\v"));
			key.erase(key.find_last_not_of("\t\n\r\f\v") + 1);
			value.erase(0, value.find_first_not_of("\t\n\r\f\v"));
			value.erase(value.find_last_not_of("\t\n\r\f\v") + 1);

			CKey bKey;
			if (value.find("+") != std::string::npos)
			{
				auto values = split_string(value, '+');
				for (auto& keyName : values)
				{
					auto keyCode = getKeyCode(keyName);
					switch (keyCode)
					{
					case KEY_LEFTSHIFT:
					case KEY_RIGHTSHIFT:
						bKey.modifier |= KEY_MOD_LSHIFT;
						break;
					case KEY_LEFTCTRL:
					case KEY_RIGHTCTRL:
						bKey.modifier |= KEY_MOD_LCTRL;
						break;
					case KEY_LEFTALT:
					case KEY_RIGHTALT:
						bKey.modifier |= KEY_MOD_LALT;
						break;
					default:
						bKey.keyCode = keyCode;
					}
				}
			}
			else bKey.keyCode = getKeyCode(value);
			
			keyMap[key] = bKey;
		}
	}

	file.close();
}