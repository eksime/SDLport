#include "xbox.h"
#include <math.h>

XINPUT_STATE state;
float deadzoneL = 0.05f;
float deadzoneR = 0.05f;

int pollController() {
	ZeroMemory(&state, sizeof(XINPUT_STATE));
  if (XInputGetState(0, &state) == ERROR_SUCCESS)
    return 1;
  return 0;
}

int getButton(int button){
	return (state.Gamepad.wButtons & button) != 0;
}

float getLT(){
  return (float)state.Gamepad.bLeftTrigger / 255;
}

float getRT(){
  return (float)state.Gamepad.bRightTrigger / 255;
}

void setDeadzoneL(float d){
  deadzoneL = d;
}

void setDeadzoneR(float d){
  deadzoneR = d;
}

float getStick(int id){
  float norm = 0;
  float dz = 0;

  switch (id) {
    case 0:
      norm = (float)state.Gamepad.sThumbLX;
      dz = deadzoneL;
      break;
    case 1:
      norm = -(float)state.Gamepad.sThumbLY;
      dz = deadzoneL;
      break;
    case 2:
      norm = (float)state.Gamepad.sThumbRX;
      dz = deadzoneR;
      break;
    case 3:
      norm = -(float)state.Gamepad.sThumbRY;
      dz = deadzoneR;
      break;
  }

  norm = max(-1.0f, norm / 32767);
  float amt = (fabsf(norm) < dz ? 0 : (fabsf(norm) - dz) * (norm / fabsf(norm)));
  if (dz > 0) amt /= 1 - dz;
  return amt;
}

