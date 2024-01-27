#include "splayer.hpp"
#include "keymap.hpp"
#include "tuner.hpp"

#include <iostream>

static double convertFractionToDouble(std::string fraction) {

	int numerator, denominator;
	size_t pos = fraction.find('/');
	if (pos == std::string::npos) {
		numerator = atoi(fraction.c_str());
		denominator = 1;
	}
	else {
		std::string numeratorStr = fraction.substr(0, pos);
		std::string denominatorStr = fraction.substr(pos + 1);
		numerator = atoi(numeratorStr.c_str());
		denominator = atoi(denominatorStr.c_str());
	}
	double value = (double)numerator / denominator;
	return value;
}

Splayer::Splayer()
{
	this->commands["d"] = &Splayer::setDuration;
	this->commands["duration"] = &Splayer::setDuration;

	this->commands["mt"] = &Splayer::setMeasureTime;
	this->commands["measuretime"] = &Splayer::setMeasureTime;

	this->commands["m"] = &Splayer::setMode;
	this->commands["mode"] = &Splayer::setMode;

	this->commands["s"] = &Splayer::setSpeed;
	this->commands["speed"] = &Splayer::setSpeed;
}

void Splayer::rest()
{
	Sleep(1.0 / (this->speed / 60.0) * (this->measureTime * this->duration) * 1000);
}

void Splayer::knock(const std::vector<std::string>& pitches)
{
	std::vector<CKey> keys;
	for (auto& pitch : pitches)
	{
		std::cout << pitch << " ";
		
		if (keyMap.find(pitch) != keyMap.end())
			keys.push_back(keyMap[pitch]);
		else std::cerr << "未找到对应按键：" << pitch;
	}
	
	std::set<CKey> set(keys.begin(), keys.end());
	
	press(set);
	this->rest();
	uplift(set);
}

void Splayer::call(const std::string& command, const std::string& parameter)
{
	if (this->commands.find(command) != commands.end())
		(this->*commands[command])(parameter);
	else
		std::cerr << "无效的命令：" << command << std::endl;
}

void Splayer::setDuration(const std::string& parameter)
{
	std::cout << "设置时值：" << parameter << std::endl;
	this->duration = convertFractionToDouble(parameter);
}

void Splayer::setMeasureTime(const std::string& parameter)
{
	std::cout << "设置节拍：" << parameter << std::endl;
	size_t pos = parameter.find('/');
	if (pos == std::string::npos)
		return;
	std::string mt = parameter.substr(pos + 1);
	this->measureTime = atoi(mt.c_str());
}

void Splayer::setMode(const std::string& parameter)
{
	std::cout << "设置调式：" << parameter << std::endl;
	this->mode = parameter;
}

void Splayer::setSpeed(const std::string& parameter)
{
	int speed = std::stoi(parameter);
	std::cout << "设置速度：" << speed << std::endl;
	this->speed = static_cast<unsigned short>(speed);
}