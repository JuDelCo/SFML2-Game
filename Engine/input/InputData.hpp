// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef INPUT_DATA_HPP
#define INPUT_DATA_HPP

#include <memory>

#define NUMBER_OF_KEYS (sizeof(KeyInfo)/sizeof(Key))

typedef struct
{
	bool value;
	char ascii;
	int sdlKey;
} Key;

typedef std::shared_ptr<Key> KeyPtr;

typedef struct
{
	Key A;
	Key B;
	Key C;
	Key D;
	Key E;
	Key F;
	Key G;
	Key H;
	Key I;
	Key J;
	Key K;
	Key L;
	Key M;
	Key N;
	Key O;
	Key P;
	Key Q;
	Key R;
	Key S;
	Key T;
	Key U;
	Key V;
	Key W;
	Key X;
	Key Y;
	Key Z;
	Key Num0;
	Key Num1;
	Key Num2;
	Key Num3;
	Key Num4;
	Key Num5;
	Key Num6;
	Key Num7;
	Key Num8;
	Key Num9;
	Key Escape;
	Key LControl;
	Key LShift;
	Key LAlt;
	Key LSystem;
	Key RControl;
	Key RShift;
	Key RAlt;
	Key RSystem;
	Key Menu;
	Key LBracket;
	Key RBracket;
	Key SemiColon;
	Key Comma;
	Key Period;
	Key Quote;
	Key Slash;
	Key BackSlash;
	Key Tilde;
	Key Equal;
	Key Dash;
	Key Space;
	Key Return;
	Key Back;
	Key Tab;
	Key PageUp;
	Key PageDown;
	Key End;
	Key Home;
	Key Insert;
	Key Delete;
	Key Add;
	Key Subtract;
	Key Multiply;
	Key Divide;
	Key Left;
	Key Right;
	Key Up;
	Key Down;
	Key Numpad0;
	Key Numpad1;
	Key Numpad2;
	Key Numpad3;
	Key Numpad4;
	Key Numpad5;
	Key Numpad6;
	Key Numpad7;
	Key Numpad8;
	Key Numpad9;
	Key F1;
	Key F2;
	Key F3;
	Key F4;
	Key F5;
	Key F6;
	Key F7;
	Key F8;
	Key F9;
	Key F10;
	Key F11;
	Key F12;
	Key F13;
	Key F14;
	Key F15;
	Key Pause;
} KeyInfo;

typedef std::shared_ptr<KeyInfo> KeyInfoPtr;

enum KeyId
{
	A = 0,
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
	Num0,
	Num1,
	Num2,
	Num3,
	Num4,
	Num5,
	Num6,
	Num7,
	Num8,
	Num9,
	Escape,
	LControl,
	LShift,
	LAlt,
	LSystem,
	RControl,
	RShift,
	RAlt,
	RSystem,
	Menu,
	LBracket,
	RBracket,
	SemiColon,
	Comma,
	Period,
	Quote,
	Slash,
	BackSlash,
	Tilde,
	Equal,
	Dash,
	Space,
	Return,
	Back,
	Tab,
	PageUp,
	PageDown,
	End,
	Home,
	Insert,
	Delete,
	Add,
	Subtract,
	Multiply,
	Divide,
	Left,
	Right,
	Up,
	Down,
	Numpad0,
	Numpad1,
	Numpad2,
	Numpad3,
	Numpad4,
	Numpad5,
	Numpad6,
	Numpad7,
	Numpad8,
	Numpad9,
	F1,
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
	F13,
	F14,
	F15,
	Pause
};

static const KeyInfo KEY_CONFIG =
{
	{ 0, 'a',  0 },         // A
	{ 0, 'b',  1 },         // B
	{ 0, 'c',  2 },         // C
	{ 0, 'd',  3 },         // D
	{ 0, 'e',  4 },         // E
	{ 0, 'f',  5 },         // F
	{ 0, 'g',  6 },         // G
	{ 0, 'h',  7 },         // H
	{ 0, 'i',  8 },         // I
	{ 0, 'j',  9 },         // J
	{ 0, 'k',  10 },        // K
	{ 0, 'l',  11 },        // L
	{ 0, 'm',  12 },        // M
	{ 0, 'n',  13 },        // N
	{ 0, 'o',  14 },        // O
	{ 0, 'p',  15 },        // P
	{ 0, 'q',  16 },        // Q
	{ 0, 'r',  17 },        // R
	{ 0, 's',  18 },        // S
	{ 0, 't',  19 },        // T
	{ 0, 'u',  20 },        // U
	{ 0, 'v',  21 },        // V
	{ 0, 'w',  22 },        // W
	{ 0, 'x',  23 },        // X
	{ 0, 'y',  24 },        // Y
	{ 0, 'z',  25 },        // Z
	{ 0, '0',  26 },        // Num0
	{ 0, '1',  27 },        // Num1
	{ 0, '2',  28 },        // Num2
	{ 0, '3',  29 },        // Num3
	{ 0, '4',  30 },        // Num4
	{ 0, '5',  31 },        // Num5
	{ 0, '6',  32 },        // Num6
	{ 0, '7',  33 },        // Num7
	{ 0, '8',  34 },        // Num8
	{ 0, '9',  35 },        // Num9
	{ 0, '\0', 36 },        // Escape
	{ 0, '\0', 37 },        // LControl
	{ 0, '\0', 38 },        // LShift
	{ 0, '\0', 39 },        // LAlt
	{ 0, '\0', 40 },        // LSystem
	{ 0, '\0', 41 },        // RControl
	{ 0, '\0', 42 },        // RShift
	{ 0, '\0', 43 },        // RAlt
	{ 0, '\0', 44 },        // RSystem
	{ 0, '\0', 45 },        // Menu
	{ 0, '[',  46 },        // LBracket
	{ 0, ']',  47 },        // RBracket
	{ 0, ';',  48 },        // SemiColon
	{ 0, ',',  49 },        // Comma
	{ 0, '.',  50 },        // Period
	{ 0, '\'', 51 },        // Quote
	{ 0, '/',  52 },        // Slash
	{ 0, '\\', 53 },        // BackSlash
	{ 0, '~',  54 },        // Tilde
	{ 0, '=',  55 },        // Equal
	{ 0, '-',  56 },        // Dash
	{ 0, ' ',  57 },        // Space
	{ 0, '\n', 58 },        // Return
	{ 0, '\0', 59 },        // Back
	{ 0, '\t', 60 },        // Tab
	{ 0, '\0', 61 },        // PageUp
	{ 0, '\0', 62 },        // PageDown
	{ 0, '\0', 63 },        // End
	{ 0, '\0', 64 },        // Home
	{ 0, '\0', 65 },        // Insert
	{ 0, '\0', 66 },        // Delete
	{ 0, '+',  67 },        // Add
	{ 0, '-',  68 },        // Subtract
	{ 0, '*',  69 },        // Multiply
	{ 0, '/',  70 },        // Divide
	{ 0, '\0', 71 },        // Left
	{ 0, '\0', 72 },        // Right
	{ 0, '\0', 73 },        // Up
	{ 0, '\0', 74 },        // Down
	{ 0, '0',  75 },        // Numpad0
	{ 0, '1',  76 },        // Numpad1
	{ 0, '2',  77 },        // Numpad2
	{ 0, '3',  78 },        // Numpad3
	{ 0, '4',  79 },        // Numpad4
	{ 0, '5',  80 },        // Numpad5
	{ 0, '6',  81 },        // Numpad6
	{ 0, '7',  82 },        // Numpad7
	{ 0, '8',  83 },        // Numpad8
	{ 0, '9',  84 },        // Numpad9
	{ 0, '\0', 85 },        // F1
	{ 0, '\0', 86 },        // F2
	{ 0, '\0', 87 },        // F3
	{ 0, '\0', 88 },        // F4
	{ 0, '\0', 89 },        // F5
	{ 0, '\0', 90 },        // F6
	{ 0, '\0', 91 },        // F7
	{ 0, '\0', 92 },        // F8
	{ 0, '\0', 93 },        // F9
	{ 0, '\0', 94 },        // F10
	{ 0, '\0', 95 },        // F11
	{ 0, '\0', 96 },        // F12
	{ 0, '\0', 97 },        // F13
	{ 0, '\0', 98 },        // F14
	{ 0, '\0', 99 },        // F15
	{ 0, '\0', 100 },       // Pause
};

typedef struct
{
	bool left;
	bool middle;
	bool right;
	bool wheelUp;
	bool wheelDown;
} MouseKey;

typedef std::shared_ptr<MouseKey> MouseKeyPtr;

typedef struct
{
	int x;
	int y;
	int xRel;
	int yRel;
	MouseKey press;
	MouseKey held;
	MouseKey up;
} MouseInfo;

typedef std::shared_ptr<MouseInfo> MouseInfoPtr;

#endif // INPUT_DATA_HPP
