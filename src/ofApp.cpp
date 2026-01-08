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
	int randomModeBezier = (int)ofRandom(0, 2);
	gridBezier = std::make_unique<GridBezier>(50,50, static_cast<GridBezier::bezierMode>(randomModeBezier));
	gridBezier->initialize(ofGetWidth(), ofGetHeight());
	gridBezier->setColorStr(getRandomColorStrategy());
	// 0.5 detik duration
	gridBezier->setAnimationStr(getRandomAnimationStrategy());
}

//--------------------------------------------------------------
void ofApp::update(){
	if (showShape)gridBezier->updateAnimation();
}

//--------------------------------------------------------------
void ofApp::draw(){
	initTrailsBackground();
	if(showShape)gridBezier->display();
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
	gridBezier->resetAnimation();
	int randomModeBezier = (int)ofRandom(0, 2);
	gridBezier = std::make_unique<GridBezier>(50, 50, static_cast<GridBezier::bezierMode>(randomModeBezier));
	gridBezier->initialize(ofGetWidth(), ofGetHeight());
	gridBezier->setColorStr(getRandomColorStrategy());
	gridBezier->setAnimationStr(getRandomAnimationStrategy());
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
	if (gridBezier->currentBzMode == GridBezier::MULURLR) {
		randomAnim = (int)ofRandom(0, 4);  // Exclude Wave
	}
	else {
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
