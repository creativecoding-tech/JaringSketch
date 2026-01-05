#pragma once
#include "../strategy/ColorStrategy.h"
class SolidColor : public ColorStrategy {
public:
  ofColor c;
  SolidColor(ofColor c);
  ofColor getColor(int i, int j, int cols, int rows) override;
};
