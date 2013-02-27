#include "Tree.h"

void Tree::init(Audio440& aud,Kinect440& kin,ColorTheme& the){

	audio = &aud;
	kinect = &kin;
	theme = &the;
	mesh = ofMesh();
	age = 0;
	introCounter = 0;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	scan = Scanlines();
	direction = ofVec3f(0,0,200);
	fbo.allocate(ofGetWidth(),ofGetHeight());
	offset = 0;
	prevamp = 0;
	basic.load("shaders/basic");
	generate();
	light.setup();
	light.setPointLight();
	light.setPosition(ofGetWidth()/2,ofGetHeight()/2,0);
	

	
	

} 
void Tree::queueIntro(){
	
	isIntro = true;
	isOutro = false;
	isCleanup = false;
	
} 
void Tree::draw(){
	
	if(!isCleanup) {
		basic.begin();
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
		ofSetColor(theme->color3);
		ofSphere((audio->getAmp()*80)*(introCounter/200));
		ofPopMatrix();
		ofPopStyle();
		basic.end();
	}

	if(isIntro && introCounter < 200) {
			introCounter+= 10;
		}else if(isIntro){
			isIntro = false;
		}

		if(isOutro && introCounter > 0) {
			introCounter-= 10;
		}else if(isOutro) {
			isOutro = false;
			isCleanup = true;
		}


} 

void Tree::generate() {
	

}
	
void Tree::update(){
} 
void Tree::queueOutro(){
	isOutro = true;
	isIntro = false;
} 
bool Tree::getCleanupState(){
	return isCleanup;
} //return a value that specifies the cleanup is over