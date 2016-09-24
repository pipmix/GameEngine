#pragma once
#include "Headers.h"
#include "Data.h"
#include "Camera.h"

extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern Data								gDat;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;
extern Camera gCam;

class Sprite {



public:

						Sprite				();
	void				SetDimensions		(float x, float y);

	void				SetAbsolute			(XMFLOAT4 a);
	void				Update				(double deltaTime);
	void				Create				();
	void				Draw				();
	void				Draw				(XMFLOAT3 p);
	void				MovePos				(XMFLOAT3 p);
	void				SetPos				(XMFLOAT3 p);
	XMFLOAT3			GetPos				();
	void				AssignResources		(UINT texID, UINT vsID, UINT psID);
	void				SetSourceRect		(int i);
	void				UpdateVertexBuffer	();
	XMFLOAT2			GetSprWH();
private:

	void				SetResources();
	XMFLOAT3			m_pos;
	XMFLOAT3			m_origin;
	XMFLOAT4			m_sourceRect;
	XMFLOAT4			m_dim;
	float				m_zd;
	ResourceIDs			m_rIds;

	UINT						m_numElements;

	ComPtr<ID3D11Buffer>		m_vertexBuffer;
	bool				m_texCoordChanged = 0;
	float				tempMove = 0.0f;
	double				m_elapsedTime = 0.0f;
	int currentFrame = 0;
	bool				m_isAnimated = true;
	bool				m_centered = false;
	XMFLOAT2 m_sprWH;

};