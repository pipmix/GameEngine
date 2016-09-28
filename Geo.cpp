#include "Geo.h"

void SphereGeo::Create(int horzSeg, int vertSeg, float radius){

	float begin = 0;
	float end = XM_2PI;

	float begin2 = 0;
	float end2 = XM_PI;
	float end3 = XM_PI;

	int numVerts = (horzSeg + 1)*(vertSeg + 1);

	XMFLOAT3* pos = new XMFLOAT3[numVerts];
	XMFLOAT3* normal = new XMFLOAT3[numVerts];
	XMFLOAT2* txcoord = new XMFLOAT2[numVerts];

	VertexPNU* verts;
	verts = new VertexPNU[numVerts];

	for (int i = 0; i < vertSeg; i++) {


	}
}
