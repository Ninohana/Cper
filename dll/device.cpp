#include "pch.h"
#include "framework.h"

#include "device.h"

#include <hidsdi.h>
#include <cfgmgr32.h>
#include <stdexcept>

HANDLE OpenVirtualDevice(const char& type)
{
	PCWSTR deviceInterface;

	switch (type)
	{
	case VIRTUAL_DEVICE_KEYBOARD:
		deviceInterface = L"\\\\?\\HID#HIDCLASS&Col04#1";
		break;
	default:
		return INVALID_HANDLE_VALUE;
	}

	GUID guid;
	HidD_GetHidGuid(&guid);

	ULONG deviceInterfaceListLength = 0;
	CONFIGRET configret = CM_Get_Device_Interface_List_Size(&deviceInterfaceListLength, &guid, nullptr, CM_GET_DEVICE_INTERFACE_LIST_PRESENT);

	if (CR_SUCCESS != configret)
		throw std::runtime_error{ "ERROR_GETTING_DEVICE_INTERFACE_LIST_SIZE" };

	if (deviceInterfaceListLength <= 1)
		throw std::runtime_error{ "ERROR_EMPTY_DEVICE_INTERFACE_LIST" };

	PWSTR deviceInterfaceList = (PWSTR)malloc(deviceInterfaceListLength * sizeof(WCHAR));

	if (nullptr == deviceInterfaceList)
		throw std::runtime_error{ "ERROR_ALLOCATING_DEVICE_INTERFACE_LIST" };

	ZeroMemory(deviceInterfaceList, deviceInterfaceListLength * sizeof(WCHAR));

	configret = CM_Get_Device_Interface_List(&guid, nullptr, deviceInterfaceList, deviceInterfaceListLength, CM_GET_DEVICE_INTERFACE_LIST_PRESENT);

	if (CR_SUCCESS != configret) {
		free(deviceInterfaceList);
		throw std::runtime_error{ "ERROR_GETTING_DEVICE_INTERFACE_LIST" };
	}

	size_t deviceInterfaceLength = wcslen(deviceInterface);
	HANDLE file = INVALID_HANDLE_VALUE;

	for (PWSTR currentInterface = deviceInterfaceList; *currentInterface; currentInterface += wcslen(currentInterface) + 1) {
		if (0 != wcsncmp(currentInterface, deviceInterface, deviceInterfaceLength)) {
			continue;
		}
		file = CreateFile(currentInterface, GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);

		if (INVALID_HANDLE_VALUE == file) {
			continue;
		}

		break;
	}

	free(deviceInterfaceList);
	if (INVALID_HANDLE_VALUE == file) {
		throw std::runtime_error{ "ERROR_INVALID_HANDLE_VALUE" };
	}

	return file;
}

API bool SendReport(HANDLE hDevice, PVOID data, DWORD size)
{
	return HidD_SetOutputReport(hDevice, data, size);
}
