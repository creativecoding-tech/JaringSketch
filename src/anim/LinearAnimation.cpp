#include "LinearAnimation.h"
#include <ofAppRunner.h>

LinearAnimation::LinearAnimation(float speed) {
	this->speed = speed;
}

void LinearAnimation::update() {

	float deltaTime = ofGetLastFrameTime();
	progress += speed * deltaTime;
	if (progress > 1) progress = 1;
}

int LinearAnimation::getValue(int target) {
	return (int)(progress * target);
}

bool LinearAnimation::isFinished() {
	return progress >= 1;
}

void LinearAnimation::reset() {
	progress = 0;
}

float LinearAnimation::getSpeed() {
	return speed;
}

void LinearAnimation::setSpeed(float speed) {
	this->speed = speed;
}

float LinearAnimation::getProgress() {
	return progress;
}