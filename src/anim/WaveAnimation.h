#pragma once
#include "../strategy/AnimationStrategy.h"
class WaveAnimation : public AnimationStrategy
{
public:
	float progress = 0;
	float speed = .5;
	float waveLength = 0.2;
	float amplitude = 0.3;
	float offset = 0;
	WaveAnimation(float speed,float waveLength,float amplitude,float offset);
	void update() override;
	int getValue(int target) override;
	void setOffset(float offset);
	bool isFinished() override;
	void reset() override;
	float getSpeed();
	void setSpeed(float speed);
	float getProgress();
};

