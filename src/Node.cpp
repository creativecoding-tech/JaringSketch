#include "Node.h"
#include <ofMath.h>

Node::Node(float startX,float startY) {
	this->startX = startX;
	this->startY = startY;
	x = startX;
	y = startY;
	targetX = startX;
	targetY = startY;
	isAnimating = false;
	animProgress = 0.0f;
	animSpeed = 0.008f;
	noiseOffset = ofRandom(0, 1000);
}

void Node::startPhyllotaxisAnimation(float targetX, float targetY) {
	this->targetX = targetX;
	this->targetY = targetY;
	isAnimating = true;
	animProgress = 0.0f;
}

void Node::updatePhyllotaxisAnimation() {
	if (!isAnimating) return;
	animProgress += animSpeed;
	if (animProgress >= 1.0f) {
		animProgress = 1.0;
		isAnimating = false;
		x = targetX;
		y = targetY;
		return;
	}
	//Cubic ease-in-out
	float t = animProgress;
	float easedT = t < 0.5 ? 4 * t * t * t : 1 
		- pow(-2 * t + 2, 3) / 2;

	//Interpolasi
	x = ofLerp(startX, targetX, easedT);
	y = ofLerp(startY, targetY, easedT);
}