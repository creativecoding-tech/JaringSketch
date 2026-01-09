#include "ofApp.h"
#include "clr/SolidColor.h"
#include "anim/LinearAnimation.h"
#include "anim/CubicEaseInOutAnimation.h"
#include "anim/EaseInOutAnimation.h"
#include "anim/WobbleAnimation.h"
#include "clr/HorizontalGradient.h"
#include "clr/RainbowSpiral.h"
#include "clr/RadialGradient.h"
#include "clr/VerticalGradient.h"
#include "clr/TimeBasedColor.h"
#include "anim/WaveAnimation.h"

//--------------------------------------------------------------
void ofApp::setup(){
	/**V - Sync sinkronisasi refersh monitor atau FPS
	* ofSetVerticalSync(true) - VSync ON 
		- openFrameworks tunggu monitor siap refresh baru gambar baru
		- Frame rate terkunci ke refresh rate monitor
		- Monitor umumnya 60Hz → FPS max = 60

	  ofSetVerticalSync(false) - VSync OFF
		- openFrameworks TIDAK tunggu monitor
		- FPS bisa secepat mungkin (unlimited)
		- Bisa mencapai ratusan FPS
	* */
	ofSetVerticalSync(false); // High Performance
	ofSetFrameRate(120); // bisa disesuaikan dengan FPS monitor, tapi tidak harus sama
	
	ofSetBackgroundAuto(false); //auto clear per frame false
	ofSetEscapeQuitsApp(false); //matikan fungsi tombol esc di keyboard
	ofBackground(0);   // Clear sekali di awal
	ofEnableAntiAliasing(); // supaya garis/bentuk menjadi smooth untuk bentuk / geometri
	ofEnableSmoothing();  // membuat smooth untuk garis atau kurva

	// Random choice: 0 = 2D, 1 = 3D
	int choice = (int)ofRandom(0, 2);
	//use3D = (choice == 1);
	//TEST
	use3D = true;

	int cellMargin = ofRandom(45, 51);

	if (use3D) {
		// Setup 3D camera
		cam.setPosition(ofGetWidth() /2, (ofGetHeight() / 2) + 100 , 811);  // Camera position
		cam.lookAt(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0)); // Look at center of grid

		// Initialize 3D GridBezier3D
		gridBezier3D = std::make_unique<GridBezier3D>(cellMargin, cellMargin);
		gridBezier3D->initialize(ofGetWidth(), ofGetHeight());
		gridBezier3D->setColorStr(getRandomColorStrategy());
		gridBezier3D->setAnimationStr(getRandomAnimationStrategy3D());
	} else {
		// Initialize 2D GridBezier
		gridBezier = std::make_unique<GridBezier>(cellMargin, cellMargin);
		gridBezier->initialize(ofGetWidth(), ofGetHeight());
		gridBezier->setColorStr(getRandomColorStrategy());
		gridBezier->setAnimationStr(getRandomAnimationStrategy());
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	if (showShape) {
		if (use3D && gridBezier3D) {
			gridBezier3D->updateAnimation();
		} else if (gridBezier) {
			gridBezier->updateAnimation();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	initTrailsBackground();
	if(showShape) {
		if (use3D && gridBezier3D) {
			// 3D rendering with camera
			cam.begin();
			gridBezier3D->display();
			cam.end();
		} else if (gridBezier) {
			// 2D rendering
			gridBezier->display();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's' || key == 'S') showShape = !showShape;
	if (key == 'q' || key == 'Q') { 
		ofExit();
	}
	if (key == 'r' || key == 'R') {
		resetGirBezier();
	}

	// Print camera position dan orientation
	if (key == 'p' || key == 'P') {
		ofVec3f pos = cam.getPosition();
		ofQuaternion orient = cam.getOrientationQuat();

		ofLog() << "========== CAMERA POSITION ==========";
		ofLog() << "Position: X=" << pos.x << ", Y=" << pos.y << ", Z=" << pos.z;
		ofLog() << "Orientation: X=" << orient.x() << ", Y=" << orient.y() << ", Z=" << orient.z() << ", W=" << orient.w();
		ofLog() << "====================================";
	}

	//set Color
	if (key == 'z' || key == 'Z') {
		gridBezier->setColorStr(std::make_unique<HorizontalGradient>(200, 280));
	}

	if (key == 'x' || key == 'X') {
		gridBezier->setColorStr(std::make_unique<RainbowSpiral>(0.5));
	}
	if (key == 'c' || key == 'C') {
		gridBezier->setColorStr(std::make_unique<RadialGradient>(0,360));
	}
	if (key == 'v' || key == 'V') {
		gridBezier->setColorStr(std::make_unique<VerticalGradient>(255, 360));
	}
	if (key == 'B' || key == 'b') {
		gridBezier->setColorStr(std::make_unique<TimeBasedColor>(125, 360, 0.25f,TimeBasedColor::WAVE));
	}

	//set Animation

	if (key == '1' || key == '1') {
		gridBezier->resetAnimation();
		gridBezier->setAnimationStr(std::make_unique<EaseInOutAnimation>(0.25f));
	}
	if (key == '2' || key == '2') {
		gridBezier->resetAnimation();
		gridBezier->setAnimationStr(std::make_unique<LinearAnimation>(0.25f));
	}
	if (key == '3' || key == '3') {
		gridBezier->resetAnimation();
		gridBezier->setAnimationStr(std::make_unique<CubicEaseInOutAnimation>(0.25f));
	}

	if (key == '4' || key == '4') {
		gridBezier->resetAnimation();
		gridBezier->setAnimationStr(std::make_unique<WobbleAnimation>(0.25f, 3, 0.7));
	}
	if (key == '5' || key == '5') {
		gridBezier->resetAnimation();
		gridBezier->setAnimationStr(std::make_unique<WaveAnimation>(0.25f, 0.2f, 0.3f, 0.0f));
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (button == 2)cursorIsVisible = !cursorIsVisible; //klik kanan
	if (cursorIsVisible) ofShowCursor();
	if (!cursorIsVisible) ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::initTrailsBackground() {
	ofSetBackgroundAuto(false);
	ofSetColor(0, ofRandom(15,21));
	ofFill();
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	ofSetLineWidth(3.0);
}

void ofApp::resetGirBezier() {
	// Random choice lagi: 0 = 2D, 1 = 3D
	int choice = (int)ofRandom(0, 2);
	//use3D = (choice == 1);
    //TEST 3D
	use3D = true;

	int cellMargin = ofRandom(45, 51);

	if (use3D) {
		// Setup 3D camera
		cam.setPosition(ofGetWidth()/2, -181, 996);  // Camera position
		cam.lookAt(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0)); // Look at center of grid
		cam.setOrientation(ofQuaternion(0.35005, 0.006934, -0.00259127, 0.936702));

		// Reset 3D GridBezier3D
		gridBezier3D = std::make_unique<GridBezier3D>(cellMargin, cellMargin);
		gridBezier3D->initialize(ofGetWidth(), ofGetHeight());
		gridBezier3D->setColorStr(getRandomColorStrategy());
		gridBezier3D->setAnimationStr(getRandomAnimationStrategy3D());
	} else {
		// Reset 2D GridBezier
		gridBezier->resetAnimation();
		gridBezier = std::make_unique<GridBezier>(cellMargin, cellMargin);
		gridBezier->initialize(ofGetWidth(), ofGetHeight());
		gridBezier->setColorStr(getRandomColorStrategy());
		gridBezier->setAnimationStr(getRandomAnimationStrategy());
	}
}

std::unique_ptr<ColorStrategy> ofApp::getRandomColorStrategy() {
	int randomColor = (int)ofRandom(0, 6);
	float startHue = ofRandom(0, 360);
	float endHue = ofRandom(0, 360);
	float speed = ofRandom(0.2f, 1.0f);
	ofColor randomC = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
	switch (randomColor) {
	case 0: return std::make_unique<SolidColor>(randomC);
	case 1: return std::make_unique<HorizontalGradient>(startHue, endHue, 80, 100);
	case 2: return std::make_unique<VerticalGradient>(startHue, endHue, 80, 100);
	case 3:  return std::make_unique<RadialGradient>(startHue, endHue, 80, 100);
	case 4: return std::make_unique<RainbowSpiral>(speed, 80, 100);
	case 5: return std::make_unique<TimeBasedColor>(startHue, endHue, speed, getRandomTimeBasedMode());
	default: return std::make_unique<SolidColor>(ofColor(255));
	}
}

TimeBasedColor::mode ofApp::getRandomTimeBasedMode() {
	int randomMode = (int)ofRandom(0, 3);
	return static_cast<TimeBasedColor::mode>(randomMode);
}

std::unique_ptr<AnimationStrategy> ofApp::getRandomAnimationStrategy() {
	int randomAnim;

	// Cek current mode dari gridBezier
	if (gridBezier && gridBezier->currentBzMode == GridBezier::MULURLR
		|| gridBezier->currentBzMode == GridBezier::WOBBLE
		|| gridBezier->currentBzMode == GridBezier::WAVE
		|| gridBezier->currentBzMode == GridBezier::RADIALWAVE
		|| gridBezier->currentBzMode == GridBezier::HORIZONTALWAVE
		|| gridBezier->currentBzMode == GridBezier::VERTICALWAVE) {
		randomAnim = (int)ofRandom(0, 4);  // Exclude Wave
	}
	else {
		// VARYING mode: WaveAnimation BOLEH dipakai (0-4)
		randomAnim = (int)ofRandom(0, 5);  // Semua animasi
	}

	switch (randomAnim) {
	case 0: return std::make_unique<LinearAnimation>(0.25f);
	case 1: return std::make_unique<EaseInOutAnimation>(0.25f);
	case 2: return std::make_unique<CubicEaseInOutAnimation>(0.25f);
	case 3: return std::make_unique<WobbleAnimation>(0.25f, 3, 0.2f);
	case 4: return std::make_unique<WaveAnimation>(0.25f, 0.2f, 0.3f, 0.0f);
	default: return std::make_unique<EaseInOutAnimation>(0.25f);
	}
}

std::unique_ptr<AnimationStrategy> ofApp::getRandomAnimationStrategy3D() {
	// Untuk 3D, semua animasi BOLEH dipakai (VARYING3D mode)
	int randomAnim = (int)ofRandom(0, 5);

	switch (randomAnim) {
	case 0: return std::make_unique<LinearAnimation>(0.25f);
	case 1: return std::make_unique<EaseInOutAnimation>(0.25f);
	case 2: return std::make_unique<CubicEaseInOutAnimation>(0.25f);
	case 3: return std::make_unique<WobbleAnimation>(0.25f, 3, 0.2f);
	case 4: return std::make_unique<WaveAnimation>(0.25f, 0.2f, 0.3f, 0.0f);
	default: return std::make_unique<EaseInOutAnimation>(0.25f);
	}
}
