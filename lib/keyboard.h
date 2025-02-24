#pragma once

#include "device.h"

class Keyboard : public Device
{
private:
#pragma pack(1)
	struct Report {
		BYTE reportId;
		BYTE modifiers;
		BYTE _reserved;
		BYTE keyCodes[6];
	};
#pragma pack()

public:
	explicit Keyboard() :Device(L"\\\\?\\HID#HIDCLASS&Col04#1") {}

	void down(BYTE* keyCodes, BYTE modifier);
	void up();

protected:
	static const BYTE REPORT_ID = { 0x04 };

	void sendReport(Report report);
};