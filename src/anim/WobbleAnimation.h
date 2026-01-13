#pragma once
#include "../strategy/AnimationStrategy.h"
class WobbleAnimation : public AnimationStrategy
{
public:
    float progress = 0;
    float speed = 0.5;
    float frequency = 3;   // Berapa getaran
    float amplitude = 0.2; // Seberapa besar wobble (20%)
    WobbleAnimation(float speed, float frequency, float amplitude);
	void update() override;
	int getValue(int target) override;
	bool isFinished() override;
	void reset() override;
	float getSpeed();
	void setSpeed(float speed);
	float getProgress();
};

