#pragma once

#ifdef DLL_EXPORTS  
#define API __declspec(dllexport)  
#else  
#define API __declspec(dllimport)  
#endif  

#include <stdlib.h>
#include <Windows.h>

class API Device
{
private:
	HANDLE mp_device;

public:
	Device(PCWSTR deviceInterface);
	~Device() = default;

protected:
	void report(PVOID data, DWORD size);

};