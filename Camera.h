#pragma once
#include "Headers.h"
#include "DataTypes.h"

extern HWND							ghWnd;

enum E_CAMERA_TYPE {
	CT_PERSP, CT_ORTHO, CT_ORTHO_2D_SIDE, CT_ORTHO_2D_TOPDOWN
};


class Camera {

public:

	// Camera Functions
					Camera();
	void			Create(E_CAMERA_TYPE ct);
	void			Update(double deltaTime);
	void			Draw();

	void			MoveTo(float posX, float posY, float posZ);
	void			MoveBy(float vecX, float vecY, float vecZ);
	void			MoveInDirection(XMFLOAT3 mv, float dist);
	void			SetTarget(XMFLOAT3& target, bool turnOnFollow);

	void			SetLookAt(XMFLOAT3 lookAT);

	void			Follow(bool turnOnFollow);



	void MoveAlongX(float x);
	void MoveAlongY(float y);
	void MoveAlongZ(float z);


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

	E_CAMERA_TYPE	m_CameraType;
	// Camera Matrices
	XMFLOAT4X4		_CameraScreenMatrix;
	XMFLOAT4X4		_CameraMatrix;
	XMFLOAT4X4		_ScreenMatrix;

	XMFLOAT4X4		_UICameraScreenMatrix;
	XMFLOAT4X4		_UIScreenMatix;;
	XMFLOAT4X4		_UICameraMatrix;

	// Camera Settings
	XMFLOAT3		_CamPosition;
	XMFLOAT3		_CamVelocity;
	XMFLOAT3		_CamLookAt;
	XMFLOAT3		_CamUpVector;

	XMFLOAT3		m_dir;
	XMFLOAT3		m_right;
	float			_CamFOVangle;
	float			_CamAspectRatio;
	float			_CamNearClip;
	float			_CamFarClip;
	bool			_IsCamPerspective;
	bool			_IsCamLookAt;

	XMFLOAT3*		_target;
	XMFLOAT3		_vel;

	long m_screenX, m_screenY;

	bool m_FollowingTarget = 0;
};

