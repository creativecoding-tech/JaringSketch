#include "EaseInOutAnimation.h"
#include <corecrt_math.h>
#include <ofLog.h>

EaseInOutAnimation::EaseInOutAnimation(float speed) {
	this->speed = speed;
}

void EaseInOutAnimation::update() {
	progress += speed;
	if (progress > 1) progress = 1;
}

int EaseInOutAnimation::getValue(int target) {
	float easeProgress = progress < 0.5
		? 2 * progress * progress                    // Ease-in
		: 1 - pow(-2 * progress + 2, 2) / 2;         // Ease-out

	return (int)(easeProgress * target);
}

bool EaseInOutAnimation::isFinished() {
	return progress >= 1;
}

void EaseInOutAnimation::reset() {
	progress = 0;
}

float EaseInOutAnimation::getSpeed() {
	return speed;
}

void EaseInOutAnimation::setSpeed(float speed) {
	this->speed = speed;
}

float EaseInOutAnimation::getProgress() {
	return progress;
}
