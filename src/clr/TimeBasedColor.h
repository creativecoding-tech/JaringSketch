#pragma once
#include "../strategy/ColorStrategy.h"
class TimeBasedColor : public ColorStrategy
{
public:
    float startHue, endHue;
    float saturation, brightness;
    float speed;
    enum mode { NORMAL, WAVE, ELAPSE};

    TimeBasedColor(float startHue, float endHue, float speed,mode currentMode);
    TimeBasedColor(float startHue, float endHue, float speed,
        float saturation, float brightness,mode currentMode);
    ofColor getColor(int i, int j, int cols, int rows) override;
    void setMode(mode valMode);

private:
    mode currentMode = NORMAL;
};

