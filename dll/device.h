#pragma once

#ifdef DLL_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif

#include <Windows.h>

#define CloseVirtualDevice CloseHandle

const char VIRTUAL_DEVICE_KEYBOARD = 0x1;

API HANDLE OpenVirtualDevice(const char& type);

API bool SendReport(HANDLE hDevice, PVOID data, DWORD size);