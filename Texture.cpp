#include "Texture.h"

Texture::Texture() {


}

void Texture::Load(std::wstring fn) {

	std::wstring s = gPath + L"Images/" + fn + L".dds";

	HRESULT hr = CreateDDSTextureFromFile(gDevice.Get(), s.c_str(), texRes.GetAddressOf(), &textureResource, DDS_ALPHA_MODE_PREMULTIPLIED);
	if (hr) Error(L"Texture Load Error", s.c_str());

	ComPtr<ID3D11Texture2D> tex2d;
	texRes.As(&tex2d);

	D3D11_TEXTURE2D_DESC td;
	tex2d->GetDesc(&td);
	pixelW = td.Width;
	pixelH = td.Height;

}

void Texture::SetInfo(int columns, int rows, int width, int height) {

	_columns = columns;
	_rows = rows;
	_width = width;
	_height = height;
	if (columns > 0 && rows > 0)_IsTileMap = true;
	else _IsTileMap = false;

}

XMFLOAT4 Texture::GetSourceRectIndex(int index) {

	_nW = 1.0f / _columns;
	_nH = 1.0f / _rows;
	_nX = (index % _columns) * _nW;
	_nY = (index / _columns) * _nH;

	return XMFLOAT4{ _nX, _nY, _nW, _nH };
}

XMFLOAT4 Texture::GetSourceRectIndex(int index_X, int index_Y) {

	_nW = 1.0f / _columns;
	_nH = 1.0f / _rows;
	_nX = index_X * _nW;
	_nY = index_Y * _nH;

	return XMFLOAT4{ _nX, _nY, _nW, _nH };
}



void Texture::LoadAsync(std::wstring fn) {
	/*
	//return type static task<void>
	return DX::ReadFileAsync(path)then([texture](const Array<byte>^ textureData)
	{
	ID3D11ShaderResourceView* srv = nullptr;
	auto device = DX::GDevice.d3dDevice.Get();
	CreateDDSTextureFromMemory(device, textureData->Data, textureData->Length, nullptr, &srv);
	texture->Load(srv);
	});
	*/
}
