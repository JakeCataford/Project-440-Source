
#include "testApp.h"
#include "ofxKinectNuiDraw.h"

#define ANIMATE_VALUES_DEBUG_440 true


//--------------------------------------------------------------
void testApp::setup() {
	
	//Inits
	kinect = Kinect440();
	midi = Midi();
	midi.init();


	ofSetLogLevel(OF_LOG_VERBOSE);
	kinect.init(kinref);
	ofSetVerticalSync(true);

	ofSetFrameRate(60);

	//Debug
	midiDebug = false;
	skeletonDebug = false;
	videoColorDebug = false;

	
	
}

//--------------------------------------------------------------
void testApp::update() {
	kinect.update();
}

//--------------------------------------------------------------
void testApp::draw() {
	ofBackground(255, 255, 255);

	if(videoColorDebug){
	kinect.drawDefaultDebugScreen();
	}
	if(skeletonDebug){
		kinect.drawSkeletonDebugScreen();
	}
	if(midiDebug){
		midi.drawDebugScreen(ANIMATE_VALUES_DEBUG_440);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch(key) {
	
	case 'm':
		midiDebug = !midiDebug;
		break;
	case 's':
		skeletonDebug = !skeletonDebug;
		break;
	case 'c':
		videoColorDebug = !videoColorDebug;
		break;
	default:
		printf("[Warning] Key not bound.\n");
		break;
	
	
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}



