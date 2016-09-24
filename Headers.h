#pragma once

#define WIN32_LEAN_AND_MEAN	
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <memory>
#include <Strsafe.h>
#include <string>
#include <wrl.h>
#include <vector>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <fstream>
#include <random>
#include <chrono>



#include <wrl\client.h>
#include "DDSTextureLoader.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
using namespace DirectX;
using Microsoft::WRL::ComPtr;

const std::wstring gPath = L"C:/Box/Box Sync/Data/";
