#include "Dx.h"

static TCHAR szWindowClass[] = _T("MainWindowClass");
static TCHAR szTitle[] = _T("MainWindowTitle");
static TCHAR szWindowClass2[] = _T("DirectXWindowClass");
static TCHAR szTitle2[] = _T("DirectXWindowTitle");

HINSTANCE hInst;
HWND hMainWindow;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);

using Microsoft::WRL::ComPtr;




ComPtr<ID3D11Device>			gDevice		= nullptr;
ComPtr<ID3D11DeviceContext>		gContext	= nullptr;
ComPtr<ID3D11DeviceContext>		gDContext	= nullptr;
ComPtr<ID3D11Buffer>			gcbPerMesh	= nullptr;
ComPtr<ID3D11Buffer>			gcbPerFrame = nullptr;
Data gDat;
HWND hWnd; //dx window





int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	int mainW = 1600;
	int mainH = 900;
	int dxWinW = 1360;
	int dxWinH = 768;
	int sX = 50;
	int sY = 50;

	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_GRAYTEXT);//  (HBRUSH)(COLOR_GRAYTEXT);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	RegisterClassEx(&wcex);

	hMainWindow = CreateWindowEx(WS_EX_CLIENTEDGE, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, mainW, mainH, NULL, NULL, hInstance, NULL);

	wcex.lpfnWndProc = ChildProc;
	wcex.lpszClassName = szWindowClass2;
	wcex.hbrBackground = GetSysColorBrush(COLOR_ACTIVEBORDER);

	RegisterClassEx(&wcex);

	hInst = hInstance;

	

	hWnd = CreateWindowEx(0, szWindowClass2, NULL, WS_CHILD | WS_VISIBLE , sX, sY, dxWinW, dxWinH, hMainWindow, 0, NULL, NULL);



	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	Dx dx(hWnd);
	dx.Initialize();

	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			dx.Update();
			dx.Draw();
		}
	}





	return (int)msg.wParam;



}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
		case WM_CREATE:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}


LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {


	switch (message) {
	//case WM_LBUTTONUP:
	//	break;
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);

}