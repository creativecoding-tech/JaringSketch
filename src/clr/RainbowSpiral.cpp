#include "RainbowSpiral.h"

RainbowSpiral::RainbowSpiral() : RainbowSpiral(0.5,80,90) {}
RainbowSpiral::RainbowSpiral(float speed): RainbowSpiral(speed,80,90){}
RainbowSpiral::RainbowSpiral(float speed, float saturation, float brightness) {
	this->speed = speed;
	this->saturation = saturation;
	this->brightness = brightness;
}

ofColor RainbowSpiral::getColor(int i, int j, int cols, int rows) {
	float angle = atan2(j - rows / 2.0f, i - cols / 2.0f);
	float distFromCenter = ofDist(i, j, cols / 2.0f, rows / 2.0f);

	float hue = fmod(ofRadToDeg(angle) + distFromCenter * 10 
		+ ofGetFrameNum() * speed, 360);

	float hue255 = ofMap(hue, 0, 360, 0, 255);
	float sat255 = ofMap(saturation, 0, 100, 0, 255);
	float bri255 = ofMap(brightness, 0, 100, 0, 255);

	ofColor color;
	color.setHsb(hue255, sat255, bri255);
	return color;
}