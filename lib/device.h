#pragma once

#include <Windows.h>

class Device
{
private:
	HANDLE mp_device;

public:
	Device(PCWSTR deviceInterface);
	~Device() { CloseHandle(mp_device); };

protected:
	void report(PVOID data, DWORD size);

};