// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#include <iostream>

#include "keyboard.h"
#include "cper.h"

static Keyboard* g_pKeyboard = nullptr;

BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		try
		{
			g_pKeyboard = new Keyboard();
		}
		catch (const std::exception&)
		{
			std::cout << "Cper.dll Load fail." << std::endl;
			FreeLibraryAndExitThread(hModule, -1);
		}
	case DLL_THREAD_ATTACH:
		std::cout << "Cper.dll Loaded." << std::endl;
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" {
	API void KeyDown(BYTE* keyCodes, BYTE modifier)
	{
		g_pKeyboard->down(keyCodes, modifier);
	}

	API void KeyUp()
	{
		g_pKeyboard->up();
	}
}
