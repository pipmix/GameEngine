#include "Input.h"

Input::Input(){


}




void Input::Update() {

	b = { 0 };
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &state);



	if (dwResult != ERROR_SUCCESS) {
		isConnected = 0;
		Reset();
		return;
	} // Return if not connected

	isConnected = true;


	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) b.left = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)b.right = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) b.up = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)b.down = 1;

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)b.a = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)b.b = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)b.x = 1;
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)b.y = 1;

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)b.start = 1; else b.start = 0;


	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		b.leftTriggerFloat = state.Gamepad.bLeftTrigger / 255.0f;
		b.leftTrigger = 1;
	}

	if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		b.rightTriggerFloat = state.Gamepad.bRightTrigger / 255.0f;
		b.rightTrigger = 1;
	}


	short leftDead = 5000;

	// Left Stick
	// Left X
	if (abs(state.Gamepad.sThumbLX) >= leftDead) {
		b.leftStickFloatX = (float)state.Gamepad.sThumbLX / (float)32767;
		if (b.leftStickFloatX > 0)b.leftStickIntX = 1;
		else b.leftStickIntX = -1;
	}
	// Left Y
	if (abs(state.Gamepad.sThumbLY) >= leftDead) {
		b.leftStickFloatY = (float)state.Gamepad.sThumbLY / (float)32767;
		if (b.leftStickFloatY > 0)b.leftStickIntY = 1;
		else b.leftStickIntY = -1;
	}
	// Right Stick
	// Right X
	if (abs(state.Gamepad.sThumbRX) >= leftDead) {
		b.rightStickFloatX = (float)state.Gamepad.sThumbRX / (float)32767;
		if (b.rightStickFloatX > 0)b.rightStickIntX = 1;
		else b.rightStickIntX = -1;
	}
	// Right Y
	if (abs(state.Gamepad.sThumbRY) >= leftDead) {
		b.rightStickFloatY = (float)state.Gamepad.sThumbRY / (float)32767;
		if (b.rightStickFloatY > 0)b.rightStickIntY = 1;
		else b.rightStickIntY = -1;
	}

	/*
	if (b.a && prev_b.a) bs_A = held_;
	else if (b.a && !prev_b.a) bs_A = down_;
	else if (!b.a && prev_b.a) bs_A = released_;
	else bs_A = up_;

	prev_b = b;

	*/

}


void Input::Reset() {


}


