#pragma once
#include "Headers.h"

#include <Xinput.h>
#pragma comment(lib, "xinput9_1_0.lib")


#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) );

enum bState {
	down_, up_, released_, held_
};

struct MouseData {

	float m_screenX;
	float m_screenY;
	int m_windowX;
	int m_windowY;

	int m_prevScreenX;
	int m_prevScreenY;
	int m_prevWindowX;
	int m_prevWindowY;

	bool m_buttonLeftPressed;
	bool m_buttonMiddlePressed;
	bool m_buttonRightPressed;

	bool m_prevButtonLeftPressed;
	bool m_prevButtonMiddlePressed;
	bool m_prevButtonRightPressed;

};

struct ControllerButtons {


	bool a;
	bool b;
	bool x;
	bool y;
	bool l3;
	bool r3;

	int leftStickIntX;
	int leftStickIntY;
	float leftStickFloatX;
	float leftStickFloatY;

	int rightStickIntX;
	int rightStickIntY;
	float rightStickFloatX;
	float rightStickFloatY;


	float leftTriggerFloat;
	float rightTriggerFloat;
	bool leftTrigger;
	bool rightTrigger;


	bool leftShoulder;


	bool rightShoulder;

	bool select;
	bool start;

	bool left;
	bool up;
	bool right;
	bool down;

	float leftX;
	float leftY;
	float rightX;
	float rightY;

};


class Input {


public:


	Input();

	void Update();
	//void FilterDeadZone();
	void Reset();

	ControllerButtons b;
	ControllerButtons prev_b;


	bool                    isConnected = 0;

	XINPUT_STATE            inputState;
	UINT64                  timeCheck;


	bState bs_A = up_;

	float LX = 0.0f;
	float LY = 0.0f;

	// Mouse Stuff
	MouseData m_md;

};

