#pragma once

enum class MouseButton : unsigned int
{
	Left = 1,	
	Right,

	Count
};

enum class Key : unsigned int
{
	Space = 32,
	
	Num1 = 48,
	Num2,
	Num3,
	Num4,
	Num5,
	Num6,
	Num7,
	Num8,
	Num9,
	Num0,

	A = 65,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,


	Escape = 256,
	Enter,
	Tab,
	Backspace,
	
	Delete = 261,
	
	Right,
	Left,
	Down,
	Up,
	
	PageUp,
	PageDown,
	Home,
	End,

	F1 = 290,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,

	Count
};
