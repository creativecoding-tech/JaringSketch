#pragma once

#include "ofMain.h"
#include "shp/GridBezier.h"
#include "shp/GridBezier3D.h"
#include "clr/SolidColor.h"
#include "clr/HorizontalGradient.h"
#include "clr/VerticalGradient.h"
#include "clr/RadialGradient.h"
#include "clr/RainbowSpiral.h"
#include "clr/TimeBasedColor.h"

class ofApp : public ofBaseApp{

	public:
		std::unique_ptr<GridBezier> gridBezier;
		std::unique_ptr<GridBezier3D> gridBezier3D;
		ofEasyCam cam;
		bool showShape = false;
		bool cursorIsVisible = true;
		bool use3D = false;  // flag untuk tracking 2D/3D

		// Camera animation state
		enum CameraAnimState {
			CAM_IDLE,           // Tidak ada animasi
			CAM_DELAY_TO_START, // Delay sebelum animasi ke target
			CAM_TO_TARGET,      // Animasi dari awal ke target
			CAM_TO_START,       // Animasi dari target ke awal (reverse)
			CAM_DELAY_TO_TARGET // Delay sebelum animasi ke target (reverse complete)
		};
		CameraAnimState cameraAnimState = CAM_IDLE;

		bool isAnimatingCamera = false;
		float cameraAnimationProgress = 0.0f;
		float cameraAnimationDuration = 8.0f;
		float cameraAnimationDelayTimer = 5.5f;
		ofVec3f cameraStartPos;
		ofVec3f cameraTargetPos;
		ofVec3f cameraCurrentPos;  
		ofVec3f cameraLastKnownPos;
		ofQuaternion cameraStartOrient;
		ofQuaternion cameraTargetOrient;

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
	void startCameraAnimation(bool reverse = false);
	void updateCameraAnimation();
	std::unique_ptr<ColorStrategy> getRandomColorStrategy();
	TimeBasedColor::mode getRandomTimeBasedMode();
	std::unique_ptr<AnimationStrategy> getRandomAnimationStrategy();
	std::unique_ptr<AnimationStrategy> getRandomAnimationStrategy3D();
};
