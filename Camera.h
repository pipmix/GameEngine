#pragma once
#include "Headers.h"
#include "DataTypes.h"

extern HWND							ghWnd;


class Camera {

public:

	// Camera Functions
					Camera();
	void			Create();
	void			Update(double deltaTime);
	void			Draw();

	void			MoveTo(float posX, float posY, float posZ);
	void			MoveBy(float vecX, float vecY, float vecZ);
	void			SetTarget(float tx, float ty, float tz);


	void			UpdatePerspective();
	void			UpdateOrthographic();

	const XMMATRIX	GetCameraScreenMatrix();
	const XMMATRIX	GetCameraMatrix();
	const XMMATRIX	GetScreenMatrix();

	const XMMATRIX	GetUICameraScreenMatrix();
	const XMMATRIX	GetUIScreenMatrix();
	const XMMATRIX	GetUICameraMatrix();

	XMFLOAT2		ConvertMouseCoord(XMFLOAT2 mc);

private:

	// Camera Matrices
	XMFLOAT4X4		_CameraScreenMatrix;
	XMFLOAT4X4		_CameraMatrix;
	XMFLOAT4X4		_ScreenMatrix;

	XMFLOAT4X4		_UICameraScreenMatrix;
	XMFLOAT4X4		_UIScreenMatix;;
	XMFLOAT4X4		_UICameraMatrix;

	// Camera Settings
	XMFLOAT3		_CamPosition;
	XMFLOAT3		_CamLookAt;
	XMFLOAT3		_CamUpVector;
	float			_CamFOVangle;
	float			_CamAspectRatio;
	float			_CamNearClip;
	float			_CamFarClip;
	bool			_IsCamPerspective;
	bool			_IsCamLookAt;

	XMFLOAT3		_target;
	XMFLOAT3		_vel;

	long m_screenX, m_screenY;

	bool m_FollowingTarget = 0;
};

