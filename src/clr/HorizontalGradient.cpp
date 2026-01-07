#include "HorizontalGradient.h"

HorizontalGradient::HorizontalGradient(float startHue, float endHue) 
	: HorizontalGradient(startHue,endHue,80,90) {
}

HorizontalGradient::HorizontalGradient(float startHue, float endHue,
	float saturation, float brightness) {
	this->startHue = startHue;
	this->endHue = endHue;
	this->saturation = saturation;
	this->brightness = brightness;
}

ofColor HorizontalGradient::getColor(int i, int j, int cols, int rows) {
	float pos = (float)i / cols;
	float hue = ofMap(pos, 0, 1, startHue, endHue);
	// Normalize ke range 0-255 untuk openFrameworks
	float hue255 = ofMap(hue, 0, 360, 0, 255);
	float sat255 = ofMap(saturation, 0, 100, 0, 255);
	float bri255 = ofMap(brightness, 0, 100, 0, 255);

	ofColor color;
	color.setHsb(hue255, sat255, bri255);
	return color;
}
