#pragma once
#include "Headers.h"

#define BUFSIZE MAX_PATH

#define IDM_FILE_NEW	1
#define IDM_FILE_OPEN	2
#define IDM_FILE_SETTINGS	12
#define IDM_FILE_EXIT	3

#define IDM_EDIT_COPY	4
#define IDM_EDIT_PASTE	5
#define IDM_EDIT_CUT	6

#define IDM_EDIT_STATUSCHECK	7

#define IDM_EDIT_ONTOP 8

#define IDM_WINDOW_WIREFRAME 9
#define IDM_WINDOW_SHADED 10
#define IDM_WINDOW_TEXTURED 11

#define IDM_SETTINGS_ONE 13
#define IDM_SETTINGS_TWO 14
#define IDM_SETTINGS_THREE 15
#define IDM_SETTINGS_FOUR 16

#define IDHK_CENTER		17

HTREEITEM ListViewAddItem(HWND hWnd, HTREEITEM hItem, LPWSTR lpwstr) {

	TVINSERTSTRUCT insert;
	insert = { 0 };

	insert.hParent = hItem;
	insert.hInsertAfter = TVI_LAST;
	insert.item.mask = TVIF_TEXT;
	insert.item.pszText = lpwstr;
	insert.item.cchTextMax = 10;

	//HTREEITEM test = TVM_INSERTITEM(0, &insert);
	return TreeView_InsertItem(hWnd, &insert);

}

HWND CreateSidePanel(HWND hWnd) {

	RECT rect;
	GetWindowRect(hWnd, &rect);
	HWND hSidePanel =
		CreateWindowEx(0, WC_TREEVIEW, NULL,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP |
			//TVS_HASLINES | TVS_LINESATROOT |
			TVS_HASBUTTONS | WS_BORDER | TVS_FULLROWSELECT
			, 0, 0, 120, rect.right - rect.left,
			hWnd, 0, NULL, NULL);
	//TVS_CHECKBOXES   TVS_FULLROWSELECT   TVS_EDITLABELS   TVS_INFOTIP  TVS_SHOWSELALWAYS



	HTREEITEM hRoot;


	TV_INSERTSTRUCT tvins;

	tvins = { 0 };

	tvins.hInsertAfter = TVI_ROOT;
	tvins.item.mask = TVIF_TEXT;
	tvins.item.pszText = L"Root";
	tvins.item.cchTextMax = 10;

	hRoot = TreeView_InsertItem(hSidePanel, &tvins);

	//tvins.hInsertAfter = TVI_LAST;
	//tvins.item.pszText = "Child";
	//hChild = TreeView_InsertItem(hSidePanel, &tvins);


	ListViewAddItem(hSidePanel, hRoot, L"test");
	ListViewAddItem(hSidePanel, hRoot, L"cat");
	ListViewAddItem(hSidePanel, ListViewAddItem(hSidePanel, hRoot, L"murder"), L"more");

	tvins.hInsertAfter = TVI_ROOT;
	tvins.item.mask = TVIF_TEXT;
	tvins.item.pszText = L"Root2";
	tvins.item.cchTextMax = 10;

	hRoot = TreeView_InsertItem(hSidePanel, &tvins);


	return hSidePanel;

}