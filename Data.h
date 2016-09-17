#pragma once
#include "Headers.h"
#include "Texture.h"
#include "Shader.h"
using namespace std;

enum  D_TEX							{	DT_BOX1,		DT_SET,					DT_WALKTEST,		DT_ITEMS,					DT_SIZE			};
static const wstring DT_STR[] =		{	L"box1",		L"set",					L"walkTest",		L"items_8c8r_16x16t"						};
static const TexProp DT_P[]	=		{	{0,0,0,0},		{ 7,6,16,16 },			{ 8,8,16,16 },		{ 8,8,16,16 }								};

enum D_VS							{	DV_BASIC,		DV_BASICTEXTURE,		DV_BASICMATRX,		DV_SIZE										};
static const wstring DV_STR[] =		{	L"BasicVS",		L"BasicTextureVS",		L"BasicMatrixVS",												};
static const VertexType DV_VT[] =	{	VT_P,			VT_P,					VT_P,															};

enum D_PS							{	DP_BASIC,		DP_BASICTEXTURE,		DP_BASICMATRX,		DP_SIZE										};
static const wstring DP_STR[] =		{	L"BasicPS",		L"BasicTexturePS",		L"BasicMatrixPS",												};



class Data {
public:

						Data				();
	void				LoadData			();
	void				Reset				();
	Texture*			GetTexture			(int n);
	PixelShader*		GetPixelShader		(int n);
	VertexShader*		GetVertexShader		(int n);

	int					m_curTex, m_curPS, m_curVS, m_curTopo;

private:

	Texture				m_Textures	[DT_SIZE];
	PixelShader			m_PShaders	[DV_SIZE];
	VertexShader		m_VShaders	[DP_SIZE];



};

