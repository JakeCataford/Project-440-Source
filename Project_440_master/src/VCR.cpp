#include "VCR.h"
#include <math.h>

void VCR::init(Audio440& aud,Kinect440& kin, ColorTheme& the){
	kinect = &kin;
	audio = &aud;
	theme = &the;
	scan = Scanlines();
	age = 0;
	fbo.allocate(ofGetWidth(),ofGetHeight());
	abrFbo.allocate(ofGetWidth(),ofGetHeight());
	bulge.load("shaders/bulge");
	abr.load("shaders/chrabr");
	flash.loadImage("images/flashorb.png");
	//glEnable (GL_TEXTURE_RECTANGLE_ARB);
	sph = ofPoint(41,20);
	flash.resize(ofGetHeight(),ofGetHeight());
	intro = 0.0f;
	lastAmp = 0;
	isOutro = false;
}

void VCR::queueIntro(){
	intro = 0.0f;
	isOutro = false;
	isCleanup = false;
}
void VCR::draw(){


	if(!isCleanup) {
		fbo.begin();
			ofPushMatrix();

				ofRotateY(sin((double)age/200)*5);
				//ofClear(0);
				ofBackground(0,0,0, intro*255);
				ofSetColor(theme->color2.r,theme->color2.g,theme->color2.b,(50 + audio->getAvgBin(10)*10)*intro);
				ofRect(-500,-500,500,ofGetWidth()*2,ofGetHeight()*2);


				if(audio->getAmp() - lastAmp > 0.3) {

					for(int i = 0; i < 10; i++){
					particles.push_back(VCRParticle(-100,ofRandom(0,ofGetHeight()),ofRandom(5,25),ofRandom(-1,1)));
					particles.push_back(VCRParticle(ofGetWidth() + 100,ofRandom(0,ofGetHeight()),ofRandom(-5,-25),ofRandom(-1,1)));


					}
				}

				for(int i = 0; i < particles.size(); i ++) {
					particles[i].update();
					particles[i].draw(audio->getAvgBin(i % 13));
					while(particles.size() > 200) {
						particles.erase(particles.begin());
					}
				}

				/*sdffdasfsdafsadfasdfsda
				ofPoint rHand = kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HAND_RIGHT);

				ofCircle(rHand.x, rHand.y, 50);

				for(int i = 0; i < particles.size(); i++)
				{
					if(particles[i].position.x == rHand.x){
						particles.erase(particles.begin());
					}
				}

				//asdfsdafasdfdasfasdfasdfasd*/

				ofPushStyle();
					for(int i = 0; i < 10; i++) {
						ofSetColor(255,255,255,10 * intro);
						ofRect((ofGetWidth()/10)*i +sin(age/8)*30,0,0,1,ofGetHeight() + 100);
						ofRect(0,(ofGetHeight()/10)*i + sin(age/10)*30,0,ofGetWidth() + 100,1);
					}
				ofPopStyle();

				float squoffset = (ofGetHeight()/2)/3;

				ofPushMatrix();
					ofPushStyle();
						ofSetColor(theme->color1.r,theme->color1.g,theme->color1.b);

							ofTranslate(ofGetWidth()/2,ofGetHeight()/2);

							ofPoint head = kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HEAD);
							ofPoint hip = kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE,NUI_SKELETON_POSITION_HIP_CENTER);

							float x = head.x - hip.x;
							float y = head.y - hip.y;

							float result = atan2 (y,x) * 180 / PI;

							ofRotateZ(result*2);

							//atan2 to find rad

							//rad to degrees

							//ofRotateZ(degrees * factor);



							//ofRotateZ(sin((age-20)/50)*90  +45); //This is the rotation do atan2() of head and hip, the convert to degrees and assign
							ofRotateY(sin((age - 10)/10)*30);
							for(int i = 0; i< 3; i++) {
								for(int j = 0; j < 3; j++) {
									ofRect(-ofGetHeight()/4 + squoffset*i,-ofGetHeight()/4 + squoffset* j,30,ofMap(audio->getAvgBin(i*3 + j*2),0,5,0,squoffset)*intro,ofMap(audio->getAvgBin(i*3 + j*2),0,5,0,squoffset)*intro);
								}
							}
					ofPopStyle();
				ofPopMatrix();

				ofPushMatrix();
					ofPushStyle();
						ofSetColor(theme->color1.r,theme->color1.g,theme->color1.b);
							ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
							ofRotateZ(result);
							//ofRotateZ(sin((age-10)/50)*90  +45);
							ofRotateY(sin((age - 5)/10)*30);
							for(int i = 0; i< 3; i++) {
								for(int j = 0; j < 3; j++) {
									ofRect(-ofGetHeight()/4 + squoffset*i,-ofGetHeight()/4 + squoffset* j,20,ofMap(audio->getAvgBin(1+i*3 + j*2),0,5,0,squoffset)*intro,ofMap(audio->getAvgBin(1+i*3 + j*2),0,5,0,squoffset)*intro);
								}
							}
					ofPopStyle();
				ofPopMatrix();

				ofPushMatrix();
					ofPushStyle();
						ofSetColor(theme->color3.r,theme->color3.g,theme->color3.b);

							ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
							ofRotateZ(result);      
							//ofRotateZ(sin(age/50)*90 +45);
							ofRotateY(sin((age)/10)*30);

							for(int i = 0; i< 3; i++) {
								for(int j = 0; j < 3; j++) {
									ofRect(-ofGetHeight()/4 + squoffset*i,-ofGetHeight()/4 + squoffset* j,0,ofMap(audio->getAvgBin(i*2 + j*2),0,5,0,squoffset)*intro,ofMap(audio->getAvgBin(i*2 + j*2),0,5,0,squoffset)*intro);
								}
							}
					ofPopStyle();
				ofPopMatrix();


				ofPushMatrix();
					ofPushStyle();
						ofTranslate(ofGetWidth()/4,ofGetHeight()/2);
						ofRotate(age/2);
						ofSetColor(255,255,255);
						ofRect(0,0,0,(audio->getAmp()*10)*intro,(audio->getAmp()*10)*intro);
					ofPopStyle();
				ofPopMatrix();


				ofPushMatrix();
					ofPushStyle();
						ofTranslate((ofGetWidth()/4)*3,ofGetHeight()/2);
						ofRotate(age/2);
						ofSetColor(255,255,255);
						ofRect(0,0,0,audio->getAvgBin(4)*10,(audio->getAmp()*10)*intro);
					ofPopStyle();
				ofPopMatrix();


				ofPushMatrix();
					ofPushStyle();
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE);
						ofSetColor(audio->getAmp()*45,audio->getAmp()*45,audio->getAmp()*45,(audio->getAmp()*45)*intro);
						flash.draw(sin(age/100)*ofGetWidth()/4  + ofGetWidth()/2 - flash.width/2,cos(age/100)*ofGetHeight()/4 + ofGetHeight()/2 - flash.height/2,flash.height,flash.width);
						glDisable(GL_BLEND);

					ofPopStyle();
				ofPopMatrix();

			ofPopMatrix();



			lastAmp = audio->getAmp();

			scan.draw();

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
			bulge.setUniform1f("radius", (ofMap(audio->getAvgBin(5),0,10,1.0,-0.3))*intro);


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
void VCR::update(){
	scan.update((audio->getAvgBin(0))*intro);
}
void VCR::queueOutro(){
	isOutro = true;
}

bool VCR::getCleanupState(){
	return isCleanup;
}