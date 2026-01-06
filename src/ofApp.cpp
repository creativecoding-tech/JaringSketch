#include "ofApp.h"
#include "clr/SolidColor.h"

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

	gridBezier = std::make_unique<GridBezier>(50,50);
	gridBezier->initialize(ofGetWidth(), ofGetHeight());
	gridBezier->setColorStr(std::make_unique<SolidColor>(ofColor(255)));
	// 0.5 detik duration
	gridBezier->setAnimationStr(std::make_unique<EaseInOutAnimation>(0.5f));
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
		gridBezier->resetAnimation(); 
		ofBackground(0);
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
	ofSetColor(0, 60);
	ofFill();
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	// Debug info
	ofSetColor(255, 255, 0);

	ofSetLineWidth(3.0);
}
