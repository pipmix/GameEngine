#pragma once
#include "Headers.h"


class Light {

public:

	Light();

protected:

	XMFLOAT4	m_color;
	XMFLOAT3	m_pos;
};

class PointLight : public Light{
public:
	PointLight();
	void SetPosition(XMFLOAT3 p);
	void SetColor(XMFLOAT3 c);

private:


	float		m_radius;

};

class SpotLight : public Light {
public:
	SpotLight();

private:
	float m_innerA;
	float m_outerA;
	XMFLOAT3 mUp;
	XMFLOAT3 mRight;

};

class DirectionalLight {
	XMFLOAT3 m_direction;
	XMFLOAT3 m_lightColor;
	float m_intensity;
};