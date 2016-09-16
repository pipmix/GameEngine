#pragma once

#include "Headers.h"
#include "DataTypes.h"

using namespace DirectX;

void ReadDataFromFile(LPCWSTR filename, byte** data, UINT* size);

void Error(LPCWSTR header, LPCWSTR info);

bool IntersectsFloat(XMFLOAT4& rectA, XMFLOAT4& rectB);

bool AABBIntersect2D(XMFLOAT4& rectA, XMFLOAT3& pos, XMFLOAT3& vel, XMFLOAT4& rectB);

void CreateItem(float x, float y, float z, char* type);

//bool Overlap(GameObj* obj1, GameObj* obj2);

bool InRange(float value, float min, float max);


float PercentToFloat(float percent, float dim);