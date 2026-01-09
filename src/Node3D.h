#pragma once
#include "ofMain.h"

class Node3D {
public:
	float x, y, z;
	float noiseOffset;

	Node3D(float x, float y, float z = 0);
};
