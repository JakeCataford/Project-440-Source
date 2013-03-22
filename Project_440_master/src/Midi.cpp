#include "Midi.h"

void Midi::init(Kinect440 &KinectReference) {

	bDebugMode = false;
	
	kinect = &KinectReference;

	//TODO Parse and read config settings

	// print the available output ports to the console
	ofxMidiOut::listPorts(); // via static too
	ofxMidiIn::listPorts();
	cycler = 0; //for debugging

	// connect
	midiOut.openPort(4);	// by number
	
	midiIn.openPort(4);

	midiIn.addListener(this);

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

void Midi::setVManager(VisualiserManager & visualiserManager){
	visualisers = & visualiserManager;
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
	setControllerValue(50,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HEAD).x,ofGetWidth()*0.25,ofGetWidth()*0.75,5,120,true));
	setControllerValue(51,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HEAD).y,0,ofGetHeight(),5,120,true));
	setControllerValue(52,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HIP_CENTER).x,ofGetWidth()*0.25,ofGetWidth()*0.75,5,120,true));
	setControllerValue(53,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HIP_CENTER).y,0,ofGetHeight(),5,120,true));
	setControllerValue(54,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HAND_LEFT).x,ofGetWidth()*0.25,ofGetWidth()*0.75,5,120,true));
	setControllerValue(55,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HAND_LEFT).y,0,ofGetHeight(),5,120,true));
	setControllerValue(56,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HAND_RIGHT).x,ofGetWidth()*0.25,ofGetWidth()*0.75,5,120,true));
	setControllerValue(57,ofMap(kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HAND_RIGHT).y,0,ofGetHeight(),5,120,true));
}

void Midi::newMidiMessage(ofxMidiMessage& msg) {

	//if message is a note on channel? 
	//visualisers->cycle();
	if(msg.status == 128) { 
		visualisers->cycle();
	}

}