#pragma once

#include <iostream>

enum class EKey : int
{
	UnAvailable = -1,
	Tab = 9,
	Enter = 13,
	ESC = 27,

	Key_0 = 48, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,

	A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	a = 97, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,

	UpArrow = 1000,
	DownArrow = 1001,
	LeftArrow = 1002,
	RightArrow = 1003
};

class InputReceiver
{
public:

	InputReceiver();

	static EKey ChatchInput();

	~InputReceiver();
};