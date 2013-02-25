
#include "Scanlines.h"

Scanlines::Scanlines(){
	age = 0;
	opacity = 0;
	texture = ofFbo();
	texture.allocate(ofGetWidth(),ofGetHeight());
	feather.loadImage("images/feather.png");
}


void Scanlines::update(float amp) {
	age+= 0.01;
	opacity = ofMap(amp,0,10,0,255);
}

void Scanlines::draw() {
	texture.begin();
	
	ofClear(0);
	ofPushStyle();

	int numberOfScanlines = 0;

	numberOfScanlines = floor((double) ofGetScreenHeight()/(SCANLINE_HEIGHT + SCANLINE_SPACING));
	for(int i = -6; i < numberOfScanlines+6; i++) {
		ofSetColor(255,0,0,opacity/3);
		ofRect(0,SCANLINE_HEIGHT*i + SCANLINE_SPACING*i + sin(age + 0.30)*50,0,ofGetWidth(),SCANLINE_HEIGHT);
		ofSetColor(0,255,0,opacity/2);
		ofRect(0,SCANLINE_HEIGHT*i + SCANLINE_SPACING*i + sin(age + 0.15)*50,0,ofGetWidth(),SCANLINE_HEIGHT);
		ofSetColor(0,0,0,opacity);
		ofRect(0,SCANLINE_HEIGHT*i + SCANLINE_SPACING*i + sin(age)*50,0,ofGetWidth(),SCANLINE_HEIGHT);
		

		
		
	}
	//ofClear(0,0,0,0.4);
	ofPopStyle();
	feather.draw(0, 0, 0, ofGetWidth(), ofGetHeight()); 

	texture.end();

	texture.draw(0,0);
}