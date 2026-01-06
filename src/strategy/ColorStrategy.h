#pragma once
#include <ofMain.h>
class ColorStrategy {
public:
	virtual ofColor getColor(int i, int j, int cols, int rows);
	virtual ofColor getColor(float x, float y);
	virtual ofColor getColor(int val);
	virtual ofColor getColor();
	virtual ~ColorStrategy() = default;
};