#include "WobbleAnimation.h"
#include <ofAppRunner.h>
#include <ofMathConstants.h>

WobbleAnimation::WobbleAnimation(float speed, float freq, float amp) {
	this->speed = speed;
	this->frequency = freq;
	this->amplitude = amp;
}

void WobbleAnimation::update() {
	float deltaTime = ofGetLastFrameTime();
	progress += speed * deltaTime;
	if (progress > 1) progress = 1;
}

int WobbleAnimation::getValue(int target) {
	// Decay factor: makin kecil di akhir animasi
	float decay = 1.0f - progress;

	//sinus wobble
	float wobble = sin(progress * PI * 2 * frequency) * amplitude * decay;

	//base progress + woblle effect
	float easeProgress = progress + wobble;

	// Clamp ke 0-1
	if (easeProgress < 0) easeProgress = 0;
	if (easeProgress > 1.3) easeProgress = 1.3;

	return (int)(easeProgress * target);
}

bool WobbleAnimation::isFinished() {
	return progress >= 1;
}

void WobbleAnimation::reset() {
	progress = 0;
}

float WobbleAnimation::getSpeed() {
	return speed;
}

void WobbleAnimation::setSpeed(float speed) {
	this->speed = speed;
}

float WobbleAnimation::getProgress() {
	return progress;
}
