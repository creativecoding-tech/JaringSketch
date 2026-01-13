#include "RadialGradient.h"
RadialGradient::RadialGradient(float startHue, float endHue)
	: RadialGradient(startHue, endHue,80,90) {

}

RadialGradient::RadialGradient(float startHue, float endHue, float saturation, float brightness) {
	this->startHue = startHue;
	this->endHue = endHue;
	this->saturation = saturation;
	this->brightness = brightness;
}

ofColor RadialGradient::getColor(int i, int j, int cols, int rows) {
    // Hitung jarak dari center
    float distFromCenter = ofDist(i, j, cols / 2.0f, rows / 2.0f);

    // Hitung jarak maksimum (dari center ke pojok)
    float maxDist = ofDist(0, 0, cols / 2.0f, rows / 2.0f);

    // Normalize jarak ke 0-1
    float pos = distFromCenter / maxDist;

    // Map posisi ke hue (0-360)
    float hue = ofMap(pos, 0, 1, this->startHue, this->endHue);

    // Normalize ke range 0-255 untuk openFrameworks
    float hue255 = ofMap(hue, 0, 360, 0, 255);
    float sat255 = ofMap(this->saturation, 0, 100, 0, 255);
    float bri255 = ofMap(this->brightness, 0, 100, 0, 255);

    ofColor color;
    color.setHsb(hue255, sat255, bri255);
    return color;
}
