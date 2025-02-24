#include "pch.h"
#include "framework.h"

#include "cper.h"

void KeyDown(BYTE* keyCodes, BYTE modifier)
{
	g_pKeyboard->down(keyCodes, modifier);
}

void KeyUp()
{
	g_pKeyboard->up();
}
