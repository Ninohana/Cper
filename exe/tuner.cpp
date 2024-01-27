#include "tuner.hpp"
#include "../dll/keyboard.h"
#include "../dll/device.h"

#include <mutex>
#include <vector>

static HANDLE hKeyboard = OpenVirtualDevice(VIRTUAL_DEVICE_KEYBOARD);

std::mutex mutex;

std::set<CKey> combination;

void apply(const std::set<CKey>& combination)
{
	std::vector<BYTE> keyCodes;
	BYTE modifier = KEY_NONE;
	size_t i = 0;
	for (auto it = combination.begin();it != combination.end() && i < 6;it++, i++)
	{
		keyCodes.push_back(it->keyCode);
		modifier |= it->modifier;
	}

	KeyDown(hKeyboard, keyCodes.data(), modifier);
}

void press(const std::set<CKey>& keys)
{
	mutex.lock();
	combination.insert(keys.begin(), keys.end());

	std::set<CKey> copy = combination;
	mutex.unlock();

	apply(copy);
}

void uplift(const std::set<CKey>& keys)
{
	
	mutex.lock();
	for (const auto& key : keys)
		combination.erase(key);
	std::set<CKey> copy = combination;
	mutex.unlock();

	if (combination.empty())
		KeyUp(hKeyboard);
	else apply(copy);
}