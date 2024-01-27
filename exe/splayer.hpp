#pragma once

#include <string>
#include <map>
#include <vector>

class Splayer
{
private:
	unsigned short	speed		=	60;
	double			duration	=	0.25;
	unsigned short	measureTime =	4;
	std::string		mode;

public:
	std::map<std::string, void(Splayer::*)(const std::string&)> commands;
	
	Splayer();
	~Splayer() = default;

	void rest();
	void knock(const std::vector<std::string>& pitches);

	void call(const std::string& command, const std::string& parameter);
	void setDuration(const std::string& parameter);
	void setMeasureTime(const std::string& parameter);
	void setMode(const std::string& parameter);
	void setSpeed(const std::string& parameter);
};