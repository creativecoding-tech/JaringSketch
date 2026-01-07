#include "WaveAnimation.h"
#include <ofAppRunner.h>
#include <ofMathConstants.h>

WaveAnimation::WaveAnimation(float speed, float waveLength, float amplitude,float offset) {
	this->speed = speed;
	this->waveLength = waveLength;
	this->amplitude = amplitude;
	this->offset = offset;
}


void WaveAnimation::update() {
	float deltaTime = ofGetLastFrameTime();
	progress += speed * deltaTime;
	if (progress > 1) progress = 1;
}

int WaveAnimation::getValue(int target) {
    // Shift progress berdasarkan offset
    float shiftedProgress = progress - offset;

    // Base progress dengan wave effect
    float wave = sin(shiftedProgress * PI * 2 / waveLength) * amplitude;
    float easeProgress = shiftedProgress + wave;

    if (easeProgress < 0) easeProgress = 0;
    if (easeProgress > 1.2) easeProgress = 1.2;

    return (int)(easeProgress * target);
}

void WaveAnimation::setOffset(float offset) {
    this->offset = offset;
}

bool WaveAnimation::isFinished() {
	return progress >= 1;
}

void WaveAnimation::reset() {
	progress = 0;
}

float WaveAnimation::getSpeed() {
	return speed;
}

void WaveAnimation::setSpeed(float speed) {
	this->speed = speed;
}

float WaveAnimation::getProgress() {
	return progress;
}