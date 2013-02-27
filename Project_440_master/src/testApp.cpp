
#include "testApp.h"
#include "ofxKinectNuiDraw.h"

#define ANIMATE_VALUES_DEBUG_440 false


//--------------------------------------------------------------
void testApp::setup() {
	

	
	audio = Audio440();

	kinect = Kinect440();
	midi = Midi();
	midi.init(kinect);
	audio.init();
	ofSoundStreamListDevices();
	ofSoundStreamSetup(0,2,this,48000,512,4);	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	ofSetVerticalSync(true);

	ofSetFrameRate(30);
	ofEnableSmoothing();
	//Debug
	midiDebug = false;
	skeletonDebug = false;
	videoColorDebug = false;
	audioDebug = false;
	frameRateDebug = true;
	kinect.init(kinref);

	vmanager = VisualiserManager();
	vmanager.init(audio,kinect);
	ofEnableAlphaBlending();

}

//--------------------------------------------------------------
void testApp::update() {
	kinect.update();
	vmanager.update();
	if(midiDebug) {
		midi.debugUpdate();
	}
}

//--------------------------------------------------------------
void testApp::draw() {
	ofClear(0);
	vmanager.draw();
	if(audioDebug) {
		audio.drawAudioDebug();
	}
	if(frameRateDebug) {
		ofPushStyle();
		ofSetColor(0,0,0);
		stringstream s;
		s << ofGetFrameRate();
		ofDrawBitmapString(s.str(),ofGetWindowWidth()-100,ofGetWindowHeight()-50);
		ofPopStyle();
	
	}
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
	case 'f':
		frameRateDebug = !frameRateDebug;
		break;
	case 'n':
		vmanager.cycle();
		break;
	case 'a':
		audioDebug = !audioDebug;
		break;
	case 'o':
		if(kinect.bRecord) {
			//kinect.stopRecording();	
		}else{
			//kinect.startRecording();
		}
		break;
	case 'p':
		if(kinect.bPlayback) {
			//kinect.stopPlayback();
		}else{
			//kinect.startPlayback();
		}
		break;
	case 'q':
		vmanager.theme.newTheme();
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

void testApp::audioIn(float * input, int bufferSize, int nChannels){


	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		audio.left[i] = input[i*2];
		audio.right[i] = input[i*2+1];
	}
	audio.bufferCounter++;
	
	audio.update();
}



