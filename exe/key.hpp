#pragma once

#include "keycode.h"

#include <Windows.h>

struct CKey
{
	BYTE keyCode;
	BYTE modifier;

	CKey() :keyCode(KEY_NONE), modifier(KEY_NONE) {}

	CKey(const BYTE& k, const BYTE& m) :keyCode(k), modifier(m) {}

	bool operator==(const CKey& ck) const
	{
		bool flag = false;
		flag &= ck.keyCode == this->keyCode;
		flag &= ck.modifier == this->modifier;
		return flag;
	}

	bool operator<(const CKey& ck) const
	{
		return ck.keyCode > this->keyCode;
	}

};