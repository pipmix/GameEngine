#pragma once
#include "Headers.h"

enum RS_STATES {
	RS_BS_SOLID, RS_BS_TRANSPARENCY
};


class RenderStates {
public:

private:


	ComPtr<ID3D11BlendState>		m_BS_solid;
	ComPtr<ID3D11BlendState>		m_BS_transparent;


};