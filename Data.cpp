#include "Data.h"

Data::Data() {
	Reset();
}

void Data::Reset() {
	m_curTex = m_curPS = m_curVS = m_curTopo = m_curMod = -1;
}

void Data::LoadData() {

	for (int i = 0; i < DT_SIZE; i++) {

		m_Textures[i].Load(DT_STR[i]);
		m_Textures[i].SetInfo(DT_P[i].noCols, DT_P[i].noRows, DT_P[i].tileW, DT_P[i].tileH);

	}

	for (int i = 0; i < DV_SIZE; i++) m_VShaders[i].Load(DV_STR[i], DV_VT[i]);
	for (int i = 0; i < DP_SIZE; i++) m_PShaders[i].Load(DP_STR[i]);

	for (int i = 0; i < D_MOD_SIZE; i++) m_Models[i].LoadMesh(DMOD_STR[i]);
	for (int i = 0; i < D_MOD_SIZE; i++) m_Models[i].AssignResources(DMOD_RESOURCES[i].first, DMOD_RESOURCES[i].second, DMOD_RESOURCES[i].third);


}


Texture* Data::GetTexture(int n) {
	return &m_Textures[n];
}

PixelShader* Data::GetPixelShader(int n) {
	return &m_PShaders[n];
}

VertexShader * Data::GetVertexShader(int n) {
	return &m_VShaders[n];
}

void Data::SetResources(ResourceIDs & rid){


	if (m_curTex != rid.m_textureID) {
		if (rid.m_textureID == -1) {
			m_curTex = rid.m_textureID;
		}
		else {
			gContext->PSSetShaderResources(0, 1, GetTexture(rid.m_textureID)->textureResource.GetAddressOf());
			m_curTex = rid.m_textureID;
		}
	}
	if (m_curVS != rid.m_vsID) {
		m_VShaders[rid.m_vsID].Set();
		m_curVS = rid.m_vsID;
	}
	if (m_curPS != rid.m_psID) {
		m_PShaders[rid.m_psID].Set();
		m_curPS = rid.m_psID;
	}
	if (m_curTopo != rid.m_topoID) {
		switch (rid.m_topoID) {
			case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
				gContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
				break;
			case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
				gContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
				break;
			case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
				gContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				break;
			case D3D11_PRIMITIVE_TOPOLOGY_LINELIST:
				gContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
				break;
			case D3D11_PRIMITIVE_TOPOLOGY_POINTLIST:
				gContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
				break;
		}
		m_curTopo = rid.m_topoID;

	}


}

void Data::DrawModel(int n){

	SetResources(m_Models[n].m_rIds);
	m_Models[n].Draw();


}

void Data::DrawModelAt(int n, XMFLOAT3 pos){


	SetResources(m_Models[n].m_rIds);
	m_Models[n].DrawAt(pos);


}
