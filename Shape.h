#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include "Data.h"

extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern Data								gDat;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;

class RectShape {

public:
			RectShape();
	void	Create(XMFLOAT4 r);
	void	Draw();
private:
	UINT						m_numElements;
	ComPtr<ID3D11Buffer>		m_vertexBuffer;


	void SetResources();
	ResourceIDs m_rIds;

};

class CircleShape {

public:
			CircleShape	();
	void	Create		(float rad, int seg);
	void	Draw		(XMFLOAT3 p);
	void	Draw();
	void	SetSegments	(int s);

private:
	UINT						m_numElements;
	ComPtr<ID3D11Buffer>		m_vertexBuffer;


	void SetResources();
	ResourceIDs m_rIds;



};

class PointShapes {
public:
			PointShapes();
			~PointShapes();
	void	Create(XMFLOAT3* points, int numOfPoints);
	void	Draw(XMFLOAT3 p);

	int m_numPoints;
	XMFLOAT3* m_points;

private:

	UINT						m_numElements;
	ComPtr<ID3D11Buffer>		m_vertexBuffer;


	void SetResources();
	ResourceIDs m_rIds;


};

class LevelShapes {

public:
			LevelShapes();
	void	Create(XMFLOAT4* rects, int numOfRects);
	void	Draw();
private:
	UINT						m_numElements;
	ComPtr<ID3D11Buffer>		m_vertexBuffer;


	void SetResources();
	ResourceIDs m_rIds;

};