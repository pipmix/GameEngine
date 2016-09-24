#pragma once
#include "Headers.h"

extern ComPtr<ID3D11Device>			gDevice;
extern ComPtr<ID3D11DeviceContext>	gContext;

enum class RS_BS_STATES {
	RS_BS_SOLID, RS_BS_TRANSPARENCY
};
enum class RS_RS_STATES {
	RS_RS_DEFAULT, RS_RS_WIREFRAME
};
enum class RS_SS_STATES {
	RS_SS_PIXELART
};
enum class RS_DS_STATES {
	RS_DS_DEFAULT, RS_DS_UI, RS_DS_READNOWRITE
};


class RenderStates {
public:

			RenderStates			();
	void	SetDefaults				();
	void	Create					();
	void	SetAll					();
	void	SetBlendState			(RS_BS_STATES bs);
	void	SetRasterizerState		(RS_RS_STATES rs);
	void	SetSamplerState			(RS_SS_STATES ss);
	void	SetDepthStencilState	(RS_DS_STATES ds);

private:

	UINT m_curBS, m_curSS, m_curRS, m_curDS;
	UINT m_defBS, m_defSS, m_defRS, m_defDS;

	ComPtr<ID3D11BlendState>		m_BS_solid;
	ComPtr<ID3D11BlendState>		m_BS_transparent;

	ComPtr<ID3D11SamplerState>		m_SS_pixelArt;

	ComPtr<ID3D11RasterizerState>	m_RS_default;
	ComPtr<ID3D11RasterizerState>	m_RS_wireframe;

	ComPtr<ID3D11DepthStencilState> m_DS_default;
	ComPtr<ID3D11DepthStencilState> m_DS_UI;
	ComPtr<ID3D11DepthStencilState> m_DS_ReadNoWrite;



};