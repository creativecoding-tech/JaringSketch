#include "ColorStrategy.h"
// Default implementation - return hitam (255, 255, 255)
ofColor ColorStrategy::getColor(int i, int j, int cols, int rows) {
    return ofColor(255, 255, 255);
}

ofColor ColorStrategy::getColor(float x, float y) {
    return ofColor(255, 255, 255);
}

ofColor ColorStrategy::getColor(int val) {
    return ofColor(255, 255, 255);
}

ofColor ColorStrategy::getColor() {
    return ofColor(255, 255, 255);
}