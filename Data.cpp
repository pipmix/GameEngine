#include "Data.h"

Data::Data() {
	Reset();
}

void Data::Reset() {
	m_curTex = m_curPS = m_curVS = m_curTopo = -1;
}

void Data::LoadData() {

	for (int i = 0; i < DT_SIZE; i++) {

		m_Textures[i].Load(DT_STR[i]);
		m_Textures[i].SetInfo(DT_P[i].noCols, DT_P[i].noRows, DT_P[i].tileW, DT_P[i].tileH);

	}

	for (int i = 0; i < DV_SIZE; i++) m_VShaders[i].Load(DV_STR[i], DV_VT[i]);
	for (int i = 0; i < DP_SIZE; i++) m_PShaders[i].Load(DP_STR[i]);

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