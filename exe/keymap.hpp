#pragma once

#include "key.hpp"

#include <map>
#include <string>

extern std::map<std::string, CKey> keyMap;

static int getKeyCode(const std::string& keyName)
	{
		if (keyName == "F1" || keyName == "f1")return KEY_F1;
		if (keyName == "F2" || keyName == "f2")return KEY_F2;
		if (keyName == "F3" || keyName == "f3")return KEY_F3;
		if (keyName == "F4" || keyName == "f4")return KEY_F4;
		if (keyName == "F5" || keyName == "f5")return KEY_F5;
		if (keyName == "F6" || keyName == "f6")return KEY_F6;
		if (keyName == "F7" || keyName == "f7")return KEY_F7;
		if (keyName == "F8" || keyName == "f8")return KEY_F8;
		if (keyName == "F9" || keyName == "f9")return KEY_F9;
		if (keyName == "F10" || keyName == "f10")return KEY_F10;
		if (keyName == "F11" || keyName == "f11")return KEY_F11;
		if (keyName == "F12" || keyName == "f12")return KEY_F12;

		if (keyName == "`" || keyName == "~")return KEY_GRAVE;
		if (keyName == "1" || keyName == "!" || keyName == "£¡")return KEY_1;
		if (keyName == "2" || keyName == "@")return KEY_2;
		if (keyName == "3" || keyName == "#")return KEY_3;
		if (keyName == "4" || keyName == "$" || keyName == "£¤")return KEY_4;
		if (keyName == "5" || keyName == "%")return KEY_5;
		if (keyName == "6" || keyName == "^")return KEY_6;
		if (keyName == "7" || keyName == "&")return KEY_7;
		if (keyName == "8" || keyName == "*")return KEY_8;
		if (keyName == "9" || keyName == "(" || keyName == "£¨")return KEY_9;
		if (keyName == "0" || keyName == ")" || keyName == "£©")return KEY_0;
		if (keyName == "-" || keyName == "_")return KEY_MINUS;
		if (keyName == "=" || keyName == "+")return KEY_EQUAL;
		if (keyName == "backspace" || keyName == "BACKSPACE" || keyName == "Backspace")return KEY_BACKSPACE;

		if (keyName == "tab" || keyName == "TAB" || keyName == "Tab")return KEY_TAB;
		if (keyName == "q" || keyName == "Q")return KEY_Q;
		if (keyName == "w" || keyName == "W")return KEY_W;
		if (keyName == "e" || keyName == "E")return KEY_E;
		if (keyName == "r" || keyName == "R")return KEY_R;
		if (keyName == "t" || keyName == "T")return KEY_T;
		if (keyName == "y" || keyName == "Y")return KEY_Y;
		if (keyName == "u" || keyName == "U")return KEY_U;
		if (keyName == "i" || keyName == "I")return KEY_I;
		if (keyName == "o" || keyName == "O")return KEY_O;
		if (keyName == "p" || keyName == "P")return KEY_P;
		if (keyName == "[" || keyName == "{")return KEY_LEFTBRACE;
		if (keyName == "]" || keyName == "}")return KEY_RIGHTBRACE;
		if (keyName == "\\" || keyName == "|")return KEY_BACKSLASH;

		if (keyName == "capslock" || keyName == "CAPSLOCK" || keyName == "Capslock" || keyName == "Caps Lock")return KEY_CAPSLOCK;
		if (keyName == "a" || keyName == "A")return KEY_A;
		if (keyName == "s" || keyName == "S")return KEY_S;
		if (keyName == "d" || keyName == "D")return KEY_D;
		if (keyName == "f" || keyName == "F")return KEY_F;
		if (keyName == "g" || keyName == "G")return KEY_G;
		if (keyName == "h" || keyName == "H")return KEY_H;
		if (keyName == "j" || keyName == "J")return KEY_J;
		if (keyName == "k" || keyName == "K")return KEY_K;
		if (keyName == "l" || keyName == "L")return KEY_L;
		if (keyName == ";" || keyName == ":" || keyName == "£º")return KEY_SEMICOLON;
		if (keyName == "'" || keyName == "\"" || keyName == "¡°" || keyName == "¡±")return KEY_APOSTROPHE;
		if (keyName == "enter" || keyName == "ENTER" || keyName == "Enter")return KEY_ENTER;

		if (keyName == "shift" || keyName == "SHIFT" || keyName == "LeftShift" || keyName == "LEFTSHIFT")return KEY_LEFTSHIFT;
		if (keyName == "z" || keyName == "Z")return KEY_Z;
		if (keyName == "x" || keyName == "X")return KEY_X;
		if (keyName == "c" || keyName == "C")return KEY_C;
		if (keyName == "v" || keyName == "V")return KEY_V;
		if (keyName == "b" || keyName == "B")return KEY_B;
		if (keyName == "n" || keyName == "N")return KEY_N;
		if (keyName == "m" || keyName == "M")return KEY_M;
		if (keyName == "," || keyName == "<" || keyName == "¡¶")return KEY_COMMA;
		if (keyName == "." || keyName == ">" || keyName == "¡·")return KEY_DOT;
		if (keyName == "/" || keyName == "?" || keyName == "£¿")return KEY_SLASH;
		if (keyName == "RightShift" || keyName == "RIGHTSHIFT")return KEY_RIGHTSHIFT;

		if (keyName == "ctrl" || keyName == "CTRL" || keyName == "LeftCtrl" || keyName == "LEFTCTRL")return KEY_LEFTSHIFT;
		// Left Win
		if (keyName == "alt" || keyName == "ALT" || keyName == "LeftAlt" || keyName == "LEFTALT")return KEY_LEFTALT;
		if (keyName == "space" || keyName == "SPACE" || keyName == "Space")return KEY_SPACE;
		if (keyName == "RightAlt" || keyName == "RIGHTALT")return KEY_RIGHTALT;
		// Right Win
		// Fn
		if (keyName == "RightCtrl" || keyName == "RIGHTCTRL")return KEY_RIGHTCTRL;

		if (keyName == "up" || keyName == "UP" || keyName == "Up" || keyName == "ÉÏ" || keyName == "¡ü")return KEY_UP;
		if (keyName == "down" || keyName == "DOWN" || keyName == "Down" || keyName == "ÏÂ" || keyName == "¡ý")return KEY_DOWN;
		if (keyName == "left" || keyName == "LEFT" || keyName == "Left" || keyName == "×ó" || keyName == "¡û")return KEY_LEFT;
		if (keyName == "right" || keyName == "RIGHT" || keyName == "Right" || keyName == "ÓÒ" || keyName == "¡ú")return KEY_RIGHT;

		return KEY_NONE;
	}

void getKeyMap(const std::string& filename);