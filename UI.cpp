#include "UI.h"

UI::UI(){


}

void UI::Create(){


	m_vignette.AssignResources(DT_IMGLIGHT, DV_UI, DP_BASICMATRX);
	m_vignette.SetAbsolute(XMFLOAT4{-1.0f,1.0f,1.0f,-1.0f});
	m_vignette.Create();


	m_healthBar.AssignResources(DT_HUDTOP, DV_UI, DP_BASICMATRX);
	m_healthBar.SetAbsolute(XMFLOAT4{ -0.9f, 0.9f, -0.5f, 0.7f });
	m_healthBar.Create();

}

void UI::Update(double deltaTime){

}

void UI::Draw(){
	XMFLOAT3 tmp = { 30.0f, 0.0f, 0.0f };
	m_vignette.Draw();
	m_healthBar.Draw(tmp);

}
