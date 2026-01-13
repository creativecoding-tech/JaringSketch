#include "Node3D.h"

Node3D::Node3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;

	// Posisi awal animasi
	this->startX = x;
	this->startY = y;
	this->startZ = z;

	// Posisi grid asli (tidak pernah berubah)
	this->originalGridX = x;
	this->originalGridY = y;
	this->originalGridZ = z;

	// Posisi target awal
	this->targetX = x;
	this->targetY = y;
	this->targetZ = z;

	this->noiseOffset = ofRandom(1000);  // Random offset untuk Perlin noise

	this->isAnimating = false;
	this->animProgress = 0.0f;
	this->animSpeed = 0.004f;
}

void Node3D::startPhyllotaxisAnimation(float targetX, float targetY, float targetZ) {
	this->targetX = targetX;
	this->targetY = targetY;
	this->targetZ = targetZ;
	this->isAnimating = true;
	this->animProgress = 0.0f;
}

void Node3D::updatePhyllotaxisAnimation() {
	if (!isAnimating) return;

	// Update progress
	animProgress += animSpeed;

	// Cek jika animasi selesai
	if (animProgress >= 1.0f) {
		animProgress = 1.0f;
		isAnimating = false;

		// Set ke posisi final
		x = targetX;
		y = targetY;
		z = targetZ;

		// Update startPos ke posisi terakhir
		startX = x;
		startY = y;
		startZ = z;

		return;
	}

	// Cubic ease-in-out
	float t = animProgress;
	float easedT = t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;

	// Interpolasi posisi (X, Y, Z)
	x = ofLerp(startX, targetX, easedT);
	y = ofLerp(startY, targetY, easedT);
	z = ofLerp(startZ, targetZ, easedT);
}
