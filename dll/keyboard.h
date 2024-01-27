#pragma once

#ifdef DLL_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif

#include <Windows.h>

const BYTE KEYBOAED_REPORT_ID = { 0x04 };

#pragma pack(1)
typedef struct _KEYBOAED_REPORT {
	BYTE reportId;
	BYTE modifiers;
	BYTE _reserved;
	BYTE keyCodes[6];
}Report, * PReport;
#pragma pack()

API bool KeyDown(HANDLE handle, BYTE* keyCodes, BYTE modifier);

API bool KeyUp(HANDLE handle);