#include "Heiroglyphs.h"
#include <math.h>

void Heiroglyphs::init(Audio440& aud,Kinect440& kin, ColorTheme& the){
	kinect = &kin;
	audio = &aud;
	theme = &the;
	scan = Scanlines();
	age = 0;
	fbo.allocate(ofGetWidth(),ofGetHeight());
	abrFbo.allocate(ofGetWidth(),ofGetHeight());
	bulge.load("shaders/bulge");
	abr.load("shaders/chrabr");
	testScreenOne.loadImage("images/test_screen_1.jpg");
	testScreenTwo.loadImage("images/test_screen_2.jpg");
	heiro.loadImage("images/heiroglyph.png"); //400 * 540
	//glEnable (GL_TEXTURE_RECTANGLE_ARB);
	sph = ofPoint(41,20);
	testScreenOne.resize(ofGetWidth(),ofGetHeight());
	testScreenTwo.resize(ofGetWidth(),ofGetHeight());
	
	intro = 0.0f;
	lastAmp = 0;
	isOutro = false;
	heiroNumber = ofRandom(0,3);
	pointLeftHand = ofPoint(ofGetWidth()/2 - 100, ofGetHeight()/2);
	pointRightHand = ofPoint(ofGetWidth()/2 + 100, ofGetHeight()/2);
}

void Heiroglyphs::queueIntro(){
	intro = 0.0f;
	isOutro = false;
	isCleanup = false;
}
void Heiroglyphs::draw(){


	if(!isCleanup) {
		fbo.begin();
			ofPushMatrix();
			ofPushStyle();
			ofClear(0);
			ofPushStyle();
			//ofSetColor(theme->color1);
		//	ofRect(0,0,ofGetWidth(),ofGetHeight());
			ofPopStyle();
			

			if(audio->getAvgBin(0) - lastAmp > 1) {
				screenToggle = !screenToggle;
			}

			if(audio->getAvgBin(0) - lastAmp > 0.4) {
				heiroNumber = floor(ofRandom(0,4));
			}
			ofPushStyle();
			ofSetColor(255,255,255,ofMap(audio->getAvgBin(0),0,5,0,255));
			if(screenToggle) {
				testScreenOne.draw(0,0,ofGetWidth(),ofGetHeight());
			}else{
				testScreenTwo.draw(0,0,ofGetWidth(),ofGetHeight());
			}
			ofPopStyle();

			ofPushStyle();

			ofSetColor(255,255,255,audio->getAvgBin(3)*25 + 200);
			//heiros
			switch(heiroNumber) {
			case 0:
				heiro.drawSubsection(ofGetWidth()/2 - 800,ofGetHeight()/4,400,ofGetHeight()/2,0,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2 - 400,ofGetHeight()/4,400,ofGetHeight()/2,0,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2,ofGetHeight()/4,400,ofGetHeight()/2,0,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2 + 400,ofGetHeight()/4,400,ofGetHeight()/2,0,0,400,540);
				break;
			case 1:
				heiro.drawSubsection(ofGetWidth()/2 - 800,ofGetHeight()/4,400,ofGetHeight()/2,400,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2 - 400,ofGetHeight()/4,400,ofGetHeight()/2,400,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2, ofGetHeight()/4,400,ofGetHeight()/2,400,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2 + 400,ofGetHeight()/4,400,ofGetHeight()/2,400,0,400,540);
				break;
			case 2:
				heiro.drawSubsection(ofGetWidth()/2 - 800,ofGetHeight()/4,400,ofGetHeight()/2,800,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2 - 400,ofGetHeight()/4,400,ofGetHeight()/2,800,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2,ofGetHeight()/4,400,ofGetHeight()/2,800,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2 + 400,ofGetHeight()/4,400,ofGetHeight()/2,800,0,400,540);
				break;
			case 3:
				heiro.drawSubsection(ofGetWidth()/2 - 800,ofGetHeight()/4,400,ofGetHeight()/2,1200,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2 - 400,ofGetHeight()/4,400,ofGetHeight()/2,1200,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2,ofGetHeight()/4,400,ofGetHeight()/2,1200,0,400,540);
				heiro.drawSubsection(ofGetWidth()/2 + 400,ofGetHeight()/4,400,ofGetHeight()/2,1200,0,400,540);
				break;
			default:
				break;

			}

			ofPopStyle();
			lastAmp = audio->getAvgBin(0);

			scan.draw();
			ofPopStyle();
			ofPopMatrix();

		fbo.end();


		abr.begin();

			abrFbo.begin();
				abr.setUniform1f("amount", audio->getAvgBin(5)*50);
				abr.setUniform1f("intensity", ofMap(audio->getAmp(),0,8,0.1,0.3));
				fbo.draw(0,0,ofGetWidth(),ofGetHeight());
			abrFbo.end();

		abr.end();

		bulge.begin();
			bulge.setUniform1f("width", ofGetWidth()/2);
			bulge.setUniform1f("height", ofGetHeight()/2);
			bulge.setUniform1f("radius", (ofMap(audio->getAvgBin(0),0,10,1.0,-0.2))*intro);


			fbo.draw(0,0,ofGetWidth(),ofGetHeight());


			abrFbo.draw(0,0);
		bulge.end();


	}


	if(isOutro) {
		intro-= 0.1f;
		if(intro <= 0.1) {
			isCleanup = true;
		}
	}else{
		if(intro < 1.0) {
			intro += 0.1;
		}else{
			intro = 1.0;
		}
	}

	age += 0.6;
}
void Heiroglyphs::update(){
	scan.update((audio->getAvgBin(0))*intro);
}
void Heiroglyphs::queueOutro(){
	isOutro = true;
}

bool Heiroglyphs::getCleanupState(){
	return isCleanup;
}