#include "Dx.h"
#include "Editor.h"

static TCHAR szWindowClass[] = _T("MainWindowClass");
static TCHAR szTitle[] = _T("MainWindowTitle");
static TCHAR szWindowClass2[] = _T("DirectXWindowClass");
static TCHAR szTitle2[] = _T("DirectXWindowTitle");

HINSTANCE hInst = nullptr;

HWND							ghWnd;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);

using Microsoft::WRL::ComPtr;




ComPtr<ID3D11Device>			gDevice		= nullptr;
ComPtr<ID3D11DeviceContext>		gContext	= nullptr;
ComPtr<ID3D11DeviceContext>		gDContext	= nullptr;
ComPtr<ID3D11Buffer>			gcbPerMesh	= nullptr;
ComPtr<ID3D11Buffer>			gcbPerFrame = nullptr;
Camera gCam;
Data gDat;

Input gInput;





int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	int mainW = 1600;
	int mainH = 900;


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
	hInst = hInstance;
	ghWnd = CreateWindowEx(WS_EX_CLIENTEDGE, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, mainW, mainH, NULL, NULL, hInstance, NULL);
	//wcex.lpfnWndProc = ChildProc;
	//wcex.lpszClassName = szWindowClass2;
	//wcex.hbrBackground = GetSysColorBrush(COLOR_ACTIVEBORDER);
	//RegisterClassEx(&wcex);
	//ghWnd = CreateWindowEx(0, szWindowClass2, NULL, WS_CHILD | WS_VISIBLE , 200, sY, dxWinW, dxWinH, hMainWindow, 0, NULL, NULL);


	ShowWindow(ghWnd, nCmdShow);
	UpdateWindow(ghWnd);

	//ShowWindow(ghWnd, nCmdShow);
	//UpdateWindow(ghWnd);


	//INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX),
	//	ICC_BAR_CLASSES | ICC_DATE_CLASSES | ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES |
	//	ICC_TREEVIEW_CLASSES | ICC_USEREX_CLASSES | ICC_WIN95_CLASSES };
	//InitCommonControlsEx(&icc);


	Dx dx(ghWnd);
	dx.Initialize();

	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			
			INT64 loopStartTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&loopStartTime);

			dx.Update();
			dx.Draw();

			INT64 loopEndTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&loopEndTime);


			INT64 timeDifference = loopEndTime - loopStartTime;

			float framesNeeded = (1000.0f / 60.0f);
			if (framesNeeded > timeDifference); // hold framesNeeded - timeDifference




		}
	}





	return (int)msg.wParam;



}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}


//LRESULT CALLBACK ChildProc(HWND h, UINT message, WPARAM wParam, LPARAM lParam) {


//	switch (message) {
	//case WM_LBUTTONUP:
	//	break;
	//}
	//return DefWindowProcW(h, message, wParam, lParam);

//}