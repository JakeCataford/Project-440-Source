#include "Audio440.h"

void Audio440::init() {

	for(int i = 0; i < 512; i++) {
		left[i] = 0;
		right[i] = 0;
	}

	stream.listDevices();
	stream.setDeviceID(8);
}

void Audio440::drawAudioDebug() {

	ofSetColor(0,100,0);
	ofFill();
	for(int i = 0; i < 512; i ++) {

	}

	//ofRect(0,0,0,50,ofMap(stream
	
}

float Audio440::getRawAverageAmp(int channel) {

	return 0;
}