/*
 * Xbox 360 controller abstraction layer.
 * Example Usage:
 * 
 * if (GAMEPAD_A) {
 *    //do something
 * }
 *
 */
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "XINPUT9_1_0.LIB")


int pollController();
int getButton(int btn);

float getRT();
float getLT();

void setDeadzoneL(float d);
void setDeadzoneR(float d);

float getStick(int id);

#define GAMEPAD_A (getButton(XINPUT_GAMEPAD_A))
#define GAMEPAD_B (getButton(XINPUT_GAMEPAD_B))
#define GAMEPAD_X (getButton(XINPUT_GAMEPAD_X))
#define GAMEPAD_Y (getButton(XINPUT_GAMEPAD_Y))
#define GAMEPAD_DPAD_LEFT (getButton(XINPUT_GAMEPAD_DPAD_LEFT)
#define GAMEPAD_DPAD_RIGHT (getButton(XINPUT_GAMEPAD_DPAD_RIGHT))
#define GAMEPAD_DPAD_UP (getButton(XINPUT_GAMEPAD_DPAD_UP))
#define GAMEPAD_DPAD_DOWN (getButton(XINPUT_GAMEPAD_DPAD_DOWN))
#define GAMEPAD_LB (getButton(XINPUT_GAMEPAD_LEFT_SHOULDER))
#define GAMEPAD_RB (getButton(XINPUT_GAMEPAD_RIGHT_SHOULDER))
#define GAMEPAD_LS (getButton(XINPUT_GAMEPAD_LEFT_THUMB))
#define GAMEPAD_RS (getButton(XINPUT_GAMEPAD_RIGHT_THUMB))
#define GAMEPAD_BACK (getButton(XINPUT_GAMEPAD_BACK))
#define GAMEPAD_START (getButton(XINPUT_GAMEPAD_START))
#define GAMEPAD_LT getLT()
#define GAMEPAD_RT getRT()
#define GAMEPAD_LEFT_X getStick(0)
#define GAMEPAD_LEFT_Y getStick(1)
#define GAMEPAD_RIGHT_X getStick(2)
#define GAMEPAD_RIGHT_Y getStick(3)