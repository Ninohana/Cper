#pragma once

#ifdef CPER_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif

extern "C" {
	API void KeyDown(BYTE* keyCodes, BYTE modifier);
	API void KeyUp();
}