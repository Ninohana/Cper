#include "pch.h"
#include "framework.h"

#include "keyboard.h"
#include "device.h"
#include "keycode.h"


API bool KeyDown(HANDLE handle, BYTE* keyCodes, BYTE modifier)
{
	if (handle == INVALID_HANDLE_VALUE)
		return false;
	
	Report report = {
		KEYBOAED_REPORT_ID,
		modifier,
		0,
		{ KEY_NONE, KEY_NONE, KEY_NONE ,KEY_NONE , KEY_NONE, KEY_NONE }
	};
	memcpy(report.keyCodes, keyCodes, 6);

	return SendReport(handle, &report, static_cast<DWORD>(sizeof(Report)));
}

API bool KeyUp(HANDLE handle)
{
	Report report = {
		KEYBOAED_REPORT_ID,
		KEY_NONE,
		0,
		{ KEY_NONE, KEY_NONE, KEY_NONE ,KEY_NONE , KEY_NONE, KEY_NONE }
	};

	return SendReport(handle, &report, static_cast<DWORD>(sizeof(Report)));
}