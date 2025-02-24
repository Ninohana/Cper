#pragma once

#include <Windows.h>

class Device
{
private:
	HANDLE mp_device = INVALID_HANDLE_VALUE;

public:
	Device(PCWSTR deviceInterface);
	~Device() { CloseHandle(mp_device); };

protected:
	void report(PVOID data, DWORD size);

};