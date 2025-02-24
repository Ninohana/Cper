#include "tuner.hpp"
#include "../dll/cper.h"

#include <mutex>
#include <vector>

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

	KeyDown(keyCodes.data(), modifier);
}

void press(const std::set<CKey>& keys)
{
	mutex.lock();
	combination.insert(keys.begin(), keys.end());

	std::set<CKey> copy = combination;
	mutex.unlock();

	apply(copy);
}

void release(const std::set<CKey>& keys)
{
	
	mutex.lock();
	for (const auto& key : keys)
		combination.erase(key);
	std::set<CKey> copy = combination;
	mutex.unlock();

	if (combination.empty())
		KeyUp();
	else apply(copy);
}