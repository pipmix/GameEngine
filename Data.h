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
static const VertexType DV_VT[] =	{	VT_P,			VT_P,					VT_PU,															};

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

struct AnimationStruct {
	int numFrames;
	int frameLoc[8];
};

// Animation States
enum AS_PLAYER											{	AS_PL_IDLE,		AS_PL_WALKLEFT,		AS_PL_WALKRIGHT,	AS_PL_RUNLEFT,	AS_PL_RUNRIGHT,		AS_PL_FACINGLEFT,	AS_PL_FACINGRIGHT,	AS_PL_JUMPINGLEFT,	AS_PL_JUMPINGRIGHT,		AS_PL_DEATH,		AS_DUCKINGLEFT,		AS_PL_DUCKINGRIGHT,		AS_PL_SIZE	};
static const AnimationStruct AS_PL_FRAMES[AS_PL_SIZE] = {	{ 1,0 },		{4,1,2,3,2},		{4,9,10,11,10},		{1,0},			{1,0},				{1,8},				{1,0},				{2,26,27},			{2,24,25},				{5,34,35,40,48,56},	{2,50,51},			{2,42,43}							};


