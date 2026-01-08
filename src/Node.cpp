#include "Node.h"
#include <ofMath.h>

Node::Node(float startX,float startY) {
	this->startX = startX;
	this->startY = startY;
	x = startX;
	y = startY;
	noiseOffset = ofRandom(0, 1000);
}