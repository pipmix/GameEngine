#pragma once
#include "Headers.h"
class Loader {
public:
	Loader();
	void LoadCollision();

	int numColRects;
	XMFLOAT4* colRects;
};