#include "Texture.h"



Texture::Texture() {

}

void Texture::LoadDDS(std::wstring fn) {


	std::wstring s = gPath + L"Images/" + fn + L".dds";

	HRESULT hr = CreateDDSTextureFromFile(gDevice.Get(), s.c_str(), NULL, &textureResource, NULL);
	if (hr) Error(L"Texture Load Error", s.c_str());


}

void Texture::SetInfo(int columns, int rows, int width, int height) {

	_columns = columns;
	_rows = rows;
	_width = width;
	_height = height;
	if (columns > 0 && rows > 0)_IsTileMap = true;
	else _IsTileMap = false;

}

Box Texture::GetSourceRectIndex(int index) {

	_nW = 1.0f / _columns;
	_nH = 1.0f / _rows;
	_nX = (index % _columns) * _nW;
	_nY = (index / _columns) * _nH;

	return Box{ _nX, _nY, _nW, _nH };
}

Box Texture::GetSourceRectIndex(int index_X, int index_Y) {

	_nW = 1.0f / _columns;
	_nH = 1.0f / _rows;
	_nX = index_X * _nW;
	_nY = index_Y * _nH;

	return Box{ _nX, _nY, _nW, _nH };
}



