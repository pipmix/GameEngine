#pragma once
#include "Headers.h"

struct BonenData {
	std::string m_name;
	XMMATRIX m_tMatrix;
	BonenData* m_sibling;
	BonenData* m_firstChild;

};