#include "PulseOrb.h"

void PulseOrb::init(Audio440& aud,Kinect440& kin) {

	//Set up references
	kinect = &kin;
	audio = &aud;


}

void PulseOrb::queueIntro() {
	isIntro = true;
}

void PulseOrb::queueOutro() {
	isOutro = true;
}

void PulseOrb::update() {

	counter += 0.3;

}

void PulseOrb::draw() {


	if(introMultip < 1 && isIntro) {
		introMultip += 0.01;
	}else if(isIntro){
		isIntro = false;
	}

	if(isOutro && introMultip > 0) {
		introMultip -= 0.01;
	}else if(isOutro) {

		cleanup();


	}

	if(!isClean) {
		ofPushStyle(); //Remember to handle the style matrix... were watching
		ofPushMatrix();
	



		ofPushMatrix();
		ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
		ofRotate(counter);
		ofFill();
		ofSetColor(50,250,10);
		ofSphere(200-audio->getAvgBin(4)*10*(introMultip));
		ofNoFill();
		ofSetColor(0,0,0);
		ofSphere(200-audio->getAvgBin(4)*10);
		ofPopStyle();
		ofPopMatrix();

		//Do some kinect stuff... Orb on your head!

		ofPoint p = kinect->getSkeletonJoint(kinect->FIRST_ACTIVE,NUI_SKELETON_POSITION_HEAD);

		ofPushMatrix();
		ofTranslate(p.x,p.y);
		ofRotateY(counter);
		ofFill();
		ofSetColor(50,250,10);
		ofSphere(100-audio->getAvgBin(6)*10);
		ofNoFill();
		ofSetColor(0,0,0);
		ofSphere(100-audio->getAvgBin(6)*10);
		ofPopStyle();
		ofPopMatrix();
		ofFill();
		ofPopMatrix();
	}



}

void PulseOrb::cleanup() {

	isOutro = false;
	isClean = true;

}

bool PulseOrb::getCleanupState() {
	return isClean;
}
