#pragma once

#include "Headers.h"
#include "DataTypes.h"

extern HWND ghWnd;

using namespace DirectX;

void ReadDataFromFile(LPCWSTR filename, byte** data, UINT* size);

void Error(LPCWSTR header, LPCWSTR info);

bool IntersectsFloat(XMFLOAT4& rectA, XMFLOAT4& rectB);

bool AABBIntersect2D(XMFLOAT4& rectA, XMFLOAT3& pos, XMFLOAT3& vel, XMFLOAT4& rectB);

void CreateItem(float x, float y, float z, char* type);

//bool Overlap(GameObj* obj1, GameObj* obj2);

bool InRange(float value, float min, float max);


float PercentToFloat(float percent, float dim);

XMFLOAT3 GetDistanceVector(XMFLOAT3 position, XMFLOAT3 target);

XMFLOAT3 BasicTween(XMFLOAT3& position, XMFLOAT3 target, float ease);


bool NumberInRange(int num, int minNum, int maxNum);

double GetNormalDist(double x, double y);
double GetRealDist(double x, double y);


