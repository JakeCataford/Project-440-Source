#include "Midi.h"

void Midi::init(Kinect440 &KinectReference) {

	bDebugMode = false;

	kinect = &KinectReference;

	//TODO Parse and read config settings

	// print the available output ports to the console
	ofxMidiOut::listPorts(); // via static too
	
	cycler = 0; //for debugging

	// connect
	midiOut.openPort(1);	// by number
	

	channel = 1;
	currentPgm = 0;
	note = 0;
	velocity = 0;
	for(int i = 0; i < 64; i++) {
	
		controllers[i] = i;
	
	}
	setControllerValue(0,controllers[0]);


}

Midi::~Midi() {

}

void Midi::setControllerValue(int controller,float value) {

	controllers[controller] = value;
	midiOut.sendControlChange(channel, controller, value);

}

void Midi::debugUpdate() {
	if(!bDebugMode) {
		bDebugMode = true;
	}

	setControllerValue(1,kinect->getSkeletonJoint(kinect->FIRST_ACTIVE, NUI_SKELETON_POSITION_HEAD).x);


}

void Midi::drawDebugScreen(bool scannerTest) {

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			ofColor c;
			if(!bDebugMode) {
				c = ofColor::fromHsb(180,ofMap(controllers[j + (i*8)],0,127,0,255,true),255);
			}else{
				c = ofColor::fromHsb(55,ofMap(controllers[j + (i*8)],0,127,0,255,true),255);
			}
			ofSetColor(c);
			ofFill();
			ofRect(50*j,50*i  + ofGetWindowHeight() - 400,0,50,50);
			stringstream text;
			text << (j + (i*8) + 1);
			ofSetColor(255,255,255);
			ofFill();
			ofDrawBitmapString(text.str(), j*50 + 20, i*50 + 30 + ofGetWindowHeight() - 400);
			


		}
	}

	if(scannerTest) {
		for(int b = 0; b < 64; b++) {
		
			controllers[b] = abs(sin((double)(cycler + (b*150))/1050)*127);
			setControllerValue(b,controllers[b]);
			cycler++;
		}
	}

	


}

void Midi::update() {
	setControllerValue(10,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HEAD).x,0,640,0,127,true));
	setControllerValue(11,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HAND_LEFT).y,0,480,0,127,true));
	setControllerValue(12,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HAND_RIGHT).y,0,480,0,127,true));
}