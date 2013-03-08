#include "Idle.h"

void Idle::init(Audio440& aud,Kinect440& kin, ColorTheme& the){
	kinect = &kin;
	audio = &aud;
	theme = &the;
	scan = Scanlines();
	age = 0;
	fbo.allocate(ofGetWidth(),ofGetHeight());
	shader.load("shaders/bulge");
	abr.load("shaders/chrabr");
	flash.loadImage("images/flashorb.png");
	sph = ofPoint(41,20);
	abrfbo.allocate(ofGetWidth(),ofGetHeight());
	flash.resize(ofGetHeight()*2,ofGetHeight()*2);
	intro = 0.0f;
	lastAmp = 0;
	isOutro = false;
	myfont.loadFont("fonts/DS-DIGI.ttf", 128);
	
	
}
	
void Idle::queueIntro(){
	intro = 0.0f;
	isOutro = false;
	isCleanup = false;
}
void Idle::draw(){
	

	if(!isCleanup) {
		fbo.begin();
			ofEnableAlphaBlending();
			ofClear(0);
			ofPushStyle();
			
			//ofSetColor(ofColor::fromHsb(111,200,255,40));
			ofSetColor(ofColor::fromHsb(theme->color1.getHue(), theme->color1.getSaturation(), theme->color1.getBrightness()), 40);
			ofRect(0,0,0,ofGetWidth(),ofGetHeight());
				 ofSetColor(255,255,255,255);

					
				

				
				
					//int x = ofRandom(0,100);

					//if(audio->getAmp() > 0)
					//{
					//	ofTranslate(ofRandom(0,30),ofRandom(0,30));
					//}

					myfont.drawString("Project440", (ofGetWidth()/2)-450, ofGetHeight()/2 + 50);
	
				ofPopMatrix();	

				lastAmp = audio->getAmp();
				ofPopStyle();
				ofPushMatrix();
					ofPushStyle();
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE);
						ofSetColor(audio->getAvgBin(0)*32,audio->getAvgBin(0)*32,audio->getAvgBin(0)*32,(audio->getAvgBin(0)*32)*intro);
						flash.draw(sin(age/100)*ofGetWidth()/4  + ofGetWidth()/2 - flash.width/2,cos(age/100)*ofGetHeight()/4 + ofGetHeight()/2 - flash.height/2,flash.height,flash.width);
						glDisable(GL_BLEND);
			
					ofPopStyle();
				ofPopMatrix();
				scan.draw();
			
		fbo.end();

		abrfbo.begin();
			abr.begin();
			//ofClear(0);
			abr.setUniform1f("amount", audio->getAvgBin(5)*50);
			abr.setUniform1f("intensity", ofMap(audio->getAmp(),0,8,0.1,0.3));
			fbo.draw(0,0);
			abr.end();
		abrfbo.end();

		shader.begin();
		shader.setUniform1f("width", ofGetWidth()/2);
		shader.setUniform1f("height", ofGetHeight()/2);
		shader.setUniform1f("radius", 100);
		
		
		//hblurfbo.draw(0,0);
		fbo.draw(0,0);
		abrfbo.draw(0,0);

		shader.end();

		
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
void Idle::update(){
	scan.update((audio->getAvgBin(0))*intro);
}
void Idle::queueOutro(){
	isOutro = true;
}

bool Idle::getCleanupState(){
	return isCleanup;
}