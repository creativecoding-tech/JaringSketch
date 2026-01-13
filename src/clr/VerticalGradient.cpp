#include "VerticalGradient.h"
VerticalGradient::VerticalGradient(float startHue, float endHue)
	: VerticalGradient(startHue, endHue, 80, 90) {
}

VerticalGradient::VerticalGradient(float startHue, float endHue,
	float saturation, float brightness) {
	this->startHue = startHue;
	this->endHue = endHue;
	this->saturation = saturation;
	this->brightness = brightness;
}

ofColor VerticalGradient::getColor(int i, int j, int cols, int rows) {
    // Posisi vertical (atas-bawah)
    float pos = (float)j / rows;

    // Map posisi ke hue (0-360) sesuai startHue dan endHue
    float hue = ofMap(pos, 0, 1, this->startHue, this->endHue);

    // Normalize ke range 0-255 untuk openFrameworks
    float hue255 = ofMap(hue, 0, 360, 0, 255);
    float sat255 = ofMap(this->saturation, 0, 100, 0, 255);
    float bri255 = ofMap(this->brightness, 0, 100, 0, 255);

    ofColor color;
    color.setHsb(hue255, sat255, bri255);
    return color;
}
