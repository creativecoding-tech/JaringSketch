#pragma once
#include "../strategy/ColorStrategy.h"
class HorizontalGradient : public ColorStrategy
{
public:
	float startHue, endHue;
	float saturation, brightness;
	HorizontalGradient(float startHue, float endHue);
	HorizontalGradient(float startHue, float endHue,
		float saturation,float brightness);
	ofColor getColor(int i, int j, int cols, int rows);
};

