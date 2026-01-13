#pragma once
#include "../strategy/ColorStrategy.h"
class RadialGradient : public ColorStrategy
{
public:
	float startHue, endHue;
	float saturation, brightness;
	RadialGradient(float startHue, float endHue);
	RadialGradient(float startHue, float endHue,float saturation,float brightness);
	ofColor getColor(int i, int j, int cols, int rows);
};

