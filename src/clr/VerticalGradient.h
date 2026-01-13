#pragma once
#include "../strategy/ColorStrategy.h"
class VerticalGradient : public ColorStrategy
{
public:
	float startHue, endHue;
	float saturation, brightness;
	VerticalGradient(float startHue, float endHue);
	VerticalGradient(float startHue, float endHue,
		float saturation, float brightness);
	ofColor getColor(int i, int j, int cols, int rows);
};

