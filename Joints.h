#pragma once
#include "Headers.h"


struct Joint {

	std::string m_jointName;
	XMMATRIX m_OffsetTransform;
	XMMATRIX m_transformCombined;
	Joint* m_nextSibling;
	Joint* m_firstChild;

};

struct Joint2 {
	UINT jointIndexNum;
	std::string m_jointName;
	XMMATRIX m_OffsetTransform;
	XMMATRIX m_transformCombined;
	Joint2* parent;
	Joint2* children;
	UINT numChildren;



};

struct BoneWeight {
	float weight;
	UINT index;
};

class Skelton {
public:
	Skelton();
	~Skelton();
	void UpdateJoints();

private:
	void UpdateConstantBuffer();
	void CalculateJointTransforms();
	UINT numJoints;
	Joint* joints;
	Joint* root;
};

struct VertSkinWeight {
	BoneWeight influences[4];
};