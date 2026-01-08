#pragma once

#include "ofMain.h"
#include "shp/GridBezier.h"
#include "clr/SolidColor.h"
#include "clr/HorizontalGradient.h"
#include "clr/VerticalGradient.h"
#include "clr/RadialGradient.h"
#include "clr/RainbowSpiral.h"
#include "clr/TimeBasedColor.h"

class ofApp : public ofBaseApp{

	public:
		std::unique_ptr<GridBezier> gridBezier;
		bool showShape = false;
		bool cursorIsVisible = true;
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

private:
	void initTrailsBackground();
	void resetGirBezier();
	std::unique_ptr<ColorStrategy> getRandomColorStrategy();
	TimeBasedColor::mode getRandomTimeBasedMode();
};
