#pragma once
#include "../strategy/AnimationStrategy.h"
class CubicEaseInOutAnimation : public AnimationStrategy
{
public:
	float progress = 0;
	float speed = .5;
	CubicEaseInOutAnimation(float speed);
	void update() override;
	int getValue(int target) override;
	bool isFinished() override;
	void reset() override;
	float getSpeed();
	void setSpeed(float speed);
	float getProgress();
};

