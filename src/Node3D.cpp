#include "Node3D.h"

Node3D::Node3D(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->noiseOffset = ofRandom(1000);  // Random offset untuk Perlin noise
}
