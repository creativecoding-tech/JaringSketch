#pragma once
#include "../strategy/ColorStrategy.h"
class RainbowSpiral : public ColorStrategy{
public:
	float speed;
	float saturation, brightness;
	RainbowSpiral();
	RainbowSpiral(float speed);
	RainbowSpiral(float speed, float saturation, float brightness);
	ofColor getColor(int i, int j, int cols, int rows);
};

