#include "SolidColor.h"

SolidColor::SolidColor(ofColor c) {
	this->c = c;
}

ofColor SolidColor::getColor() {
	return c;
}
