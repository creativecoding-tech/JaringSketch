#include "TimeBasedColor.h"
TimeBasedColor::TimeBasedColor(float startHue, float endHue, float speed,mode valMode)
    : TimeBasedColor(startHue, endHue, speed, 80, 100,valMode) {
}

TimeBasedColor::TimeBasedColor(float startHue, float endHue, float speed,
    float saturation, float brightness,mode valMode) {
    this->startHue = startHue;
    this->endHue = endHue;
    this->speed = speed;
    this->saturation = saturation;
    this->brightness = brightness;
    this->currentMode = valMode;
}

ofColor TimeBasedColor::getColor(int i, int j, int cols, int rows) {
    float pos;
    float hue;
    float hue255;
    float sat255;
    float bri255;
    float time;
    ofColor color;
    switch (currentMode) {
    case NORMAL:
        // Hitung hue berdasarkan waktu (frame count)
        hue = fmod(ofGetFrameNum() * speed, 360);

        // Normalize ke HSB openFrameworks
        hue255 = ofMap(hue, 0, 360, 0, 255);
        sat255 = ofMap(this->saturation, 0, 100, 0, 255);
        bri255 = ofMap(this->brightness, 0, 100, 0, 255);

        color.setHsb(hue255, sat255, bri255);
        return color;
        break;
    case WAVE:
        // Posisi horizontal (0-1)
        pos = (float)i / cols;

        // Hue = posisi + waktu
        hue = fmod((pos * 360) + ofGetFrameNum() * speed, 360);

        // Normalize ke HSB
        hue255 = ofMap(hue, 0, 360, 0, 255);
        sat255 = ofMap(this->saturation, 0, 100, 0, 255);
        bri255 = ofMap(this->brightness, 0, 100, 0, 255);
       
        color.setHsb(hue255, sat255, bri255);
        return color;
        break;
    case ELAPSE:
        // Pakai elapsed time (detik) bukan frame count
        time = ofGetElapsedTimef();  // Berapa detik sejak app start

        // Hue berputar seiring waktu
        hue = fmod(time * speed * 60, 360);  // *60 agar speed mirip frame-based

        hue255 = ofMap(hue, 0, 360, 0, 255);
        sat255 = ofMap(this->saturation, 0, 100, 0, 255);
        bri255 = ofMap(this->brightness, 0, 100, 0, 255);

        color.setHsb(hue255, sat255, bri255);
        return color;
        break;
    }
}

void TimeBasedColor::setMode(mode val) {
    this->currentMode = val;
}