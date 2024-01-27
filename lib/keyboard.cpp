#include "pch.h"
#include "framework.h"

#include "keyboard.h"
#include "device.h"
#include "keycode.h"

#include <iostream>

Keyboard::Keyboard() :Device{ L"\\\\?\\HID#VARIABLE_6&Col04#1" }
{
	std::cout << "键盘设备初始化成功" << std::endl;
}

void Keyboard::down(BYTE* keyCodes, BYTE modifier)
{
	Report report = {
		REPORT_ID,
		modifier,
		0,
		{ KEY_NONE, KEY_NONE, KEY_NONE ,KEY_NONE , KEY_NONE, KEY_NONE }
	};
	memcpy(report.keyCodes, keyCodes, 6);
	this->sendReport(report);
}

void Keyboard::up()
{
	Report report = {
		REPORT_ID,
		KEY_NONE,
		0,
		{ KEY_NONE, KEY_NONE, KEY_NONE ,KEY_NONE , KEY_NONE, KEY_NONE }
	};
	this->sendReport(report);
}

void Keyboard::sendReport(Report report)
{
	this->report(&report, static_cast<DWORD>(sizeof(Report)));
}
