#include "CubicEaseInOutAnimation.h"
#include <ofAppRunner.h>

CubicEaseInOutAnimation::CubicEaseInOutAnimation(float speed) {
	this->speed = speed;
}

void CubicEaseInOutAnimation::update() {
	/**
	deltaTime Membuat animasi/gameplay konsisten walau FPS berubah-ubah!		
	- Kalau komputer cepat: FPS tinggi, deltaTime kecil, gerakan smooth
	- Kalau komputer lambat: FPS rendah, deltaTime besar, gerakan tetap sama speed total
	- ** Gameplay konsisten!**
  **/
	float deltaTime = ofGetLastFrameTime();
	progress += speed * deltaTime;
	if (progress > 1) progress = 1;
}

int CubicEaseInOutAnimation::getValue(int target) {
	float easeProgress = progress < 0.5
		? 4 * progress * progress * progress         // Power 3 ← beda di sini!
		: 1 - pow(-2 * progress + 2, 3) / 2;         // Power 3 ← beda di sini!
	return (int)(easeProgress * target);
}

bool CubicEaseInOutAnimation::isFinished() {
	return progress >= 1;
}

void CubicEaseInOutAnimation::reset() {
	progress = 0;
}

float CubicEaseInOutAnimation::getSpeed() {
	return speed;
}

void CubicEaseInOutAnimation::setSpeed(float speed) {
	this->speed = speed;
}

float CubicEaseInOutAnimation::getProgress() {
	return progress;
}

