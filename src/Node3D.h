#pragma once
#include "ofMain.h"

class Node3D {
public:
	float x, y, z;
	float startX, startY, startZ;
	float originalGridX, originalGridY, originalGridZ;
	float targetX, targetY, targetZ;
	float noiseOffset;

	// Animasi phyllotaxis
	bool isAnimating;
	float animProgress;
	float animSpeed;

	Node3D(float x, float y, float z = 0);

	// Method phyllotaxis
	void startPhyllotaxisAnimation(float targetX, float targetY, float targetZ);
	void updatePhyllotaxisAnimation();
};
