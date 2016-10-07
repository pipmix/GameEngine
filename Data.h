#pragma once
#include "Headers.h"
#include "Texture.h"
#include "Shader.h"
using namespace std;

enum  D_TEX							{	DT_BOX1,		DT_SET,					DT_WALKTEST,		DT_ITEMS,				DT_IMGLIGHT,	DT_HUDTOP,	DT_QUICKTEST,	DT_COLORS,		DT_WALL01,	DT_CHAR,		DT_SIZE			};
static const wstring DT_STR[] =		{	L"box1",		L"set",					L"walkTest",		L"items",	L"imgLight",	L"aars",	L"quicktest",	L"hudItems",	L"wall01",		L"char",				};
static const TexProp DT_P[]	=		{	{0,0,0,0},		{ 7,6,16,16 },			{ 8,8,16,16 },		{ 8,8,16,16 },			{1,1,1,1},		{1,1,1,1},	{16,16,24,24},	{10,10,24,24},	{0,0,0,0}, {8,8,16,16},						};

enum D_VS							{	DV_BASIC,		DV_BASICTEXTURE,		DV_BASICMATRX,		DV_UI,		DV_BASICNORMAL,		DV_BASICLIGHTING,		DV_SIZE							};
static const wstring DV_STR[] =		{	L"BasicVS",		L"BasicTextureVS",		L"BasicMatrixVS",	L"UI_VS",	L"BasicNormalVS",	L"BasicLightingVS",			};
static const VertexType DV_VT[] =	{	VT_P,			VT_P,					VT_PU,				VT_PU,		VT_PNU,				VT_PNU,						};

enum D_PS							{	DP_BASIC,		DP_BASICTEXTURE,		DP_BASICMATRX,		DP_UI,		DP_BASICNORMAL,		DP_BASICLIGHTING,	DP_POSTPROCESS,		DP_SIZE							};
static const wstring DP_STR[] =		{	L"BasicPS",		L"BasicTexturePS",		L"BasicMatrixPS",	L"UI_PS",	L"BasicNormalPS",	L"BasicLightingPS",	L"PostProcessPS",		 };



class Data {
public:

						Data				();
	void				LoadData			();
	void				Reset				();
	Texture*			GetTexture			(int n);
	PixelShader*		GetPixelShader		(int n);
	VertexShader*		GetVertexShader		(int n);
	void				SetResources		(ResourceIDs& rid);

	int					m_curTex, m_curPS, m_curVS, m_curTopo;

private:

	Texture				m_Textures	[DT_SIZE];
	PixelShader			m_PShaders	[DV_SIZE];
	VertexShader		m_VShaders	[DP_SIZE];



};

struct AnimationStruct {
	int numFrames;
	bool loop;
	int frameLoc[8];
};

// Animation States
enum AS_PLAYER											{	AS_PL_IDLE,				AS_PL_WALKLEFT,				AS_PL_WALKRIGHT,		AS_PL_RUNLEFT,				AS_PL_RUNRIGHT,				AS_PL_FACINGLEFT,	AS_PL_FACINGRIGHT,	AS_PL_JUMPINGLEFT,		AS_PL_JUMPINGRIGHT,		AS_PL_DEATH,					AS_DUCKINGLEFT,				AS_PL_DUCKINGRIGHT,		AS_PL_CLIMBLEFT,		AS_PL_CLIMBRIGHT,		AS_PL_SIZE	};
static const AnimationStruct AS_PL_FRAMES[AS_PL_SIZE] = {	{ 2, true, 0,1 },		{4, true, 19,20,21,18},		{4, true, 3,4,5,2},		{3, true, 27,28,29},		{3, true, 11,12,13},		{1, false, 18},		{1, false, 2},		{3, false, 24,25,26},	{3, false, 8,9,10},		{5, false, 34,35,40,48,56},		{2,false, 50,51},			{2, false, 42,43},		{2, false, 42,43},		{ 2,false, 42,43 },						};


const XMFLOAT4 DCOLOR_black = { 0.0f, 0.0f, 0.0f, 1.0f };
const XMFLOAT4 DCOLOR_white = { 1.0f, 1.0f, 1.0f, 1.0f };