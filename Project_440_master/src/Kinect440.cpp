#include "Kinect440.h"
#include "ofxKinectNuiDraw.h"

using namespace std;

void  Kinect440::init(ofxKinectNui& kinref) {

	kinect = &kinref;

	ofxKinectNui::InitSetting initSetting;
	initSetting.grabVideo = true;
	initSetting.grabDepth = true;
	initSetting.grabAudio = true;
	initSetting.grabLabel = true;
	initSetting.grabSkeleton = true;
	initSetting.grabCalibratedVideo = true;
	initSetting.grabLabelCv = true;
	initSetting.videoResolution = NUI_IMAGE_RESOLUTION_640x480;
	initSetting.depthResolution = NUI_IMAGE_RESOLUTION_320x240;
	kinect->init(initSetting);
	kinect->open(true);

	kinect->addKinectListener(this, &Kinect440::kinectPlugged, &Kinect440::kinectUnplugged);
	kinectSource = &kinref;
	angle = kinect->getCurrentAngle();
	bRecord = false;
	bPlayback = false;
	bPlugged = kinect->isConnected();
	nearClipping = kinect->getNearClippingDistance();
	farClipping = kinect->getFarClippingDistance();
	
	bDrawVideo = false;
	bDrawDepthLabel = false;
	bDrawSkeleton = false;
	bDrawCalibratedTexture = false;
	

	videoDraw_ = ofxKinectNuiDrawTexture::createTextureForVideo(kinect->getVideoResolution());
	depthDraw_ = ofxKinectNuiDrawTexture::createTextureForDepth(kinect->getDepthResolution());
	labelDraw_ = ofxKinectNuiDrawTexture::createTextureForLabel(kinect->getDepthResolution());
	skeletonDraw_ = new ofxKinectNuiDrawSkeleton();
	kinect->setVideoDrawer(videoDraw_);
	kinect->setDepthDrawer(depthDraw_);
	kinect->setLabelDrawer(labelDraw_);
	kinect->setSkeletonDrawer(skeletonDraw_);


}

void   Kinect440::update() {
	kinectSource->update();
	if(bRecord){
		kinectRecorder.update();
	}


	for(int i = 0; i < ofxKinectNui::SKELETON_COUNT; i++) {
		if(kinect->skeletonPoints[i][0].z > 0){
			for(int j = 0; j < kinect->SKELETON_POSITION_COUNT; j++) {
			
				if(kinect->skeletonPoints[i][j].x > 0 && kinect->skeletonPoints[i][j].y) {
					//update the lerp model
					skeletonLerpModel[i][j].x += (ofMap(kinect->skeletonPoints[i][j].x,0,320,0,ofGetWindowWidth()) - skeletonLerpModel[i][j].x)*0.5;
					skeletonLerpModel[i][j].y += (ofMap(kinect->skeletonPoints[i][j].y,0,240,0,ofGetWindowHeight()) - skeletonLerpModel[i][j].y)*0.5;
					// ATM z is only used to check skeleton validity
				}


			

			}
		}
	}
}


void Kinect440::drawSkeletonDebugScreen() {

	stringstream s;
	s << "Kinect Skeleton Debugger:\n"
	<< "red is the raw values, maroon is the Lerped vals, green is the mapped vals, displaying Raw vals numerically\n";
	
	//kinect->drawVideo(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	ofEnableAlphaBlending();
	kinect->drawLabel(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); //Lets Draw the players
	ofDisableAlphaBlending();
	kinect->drawSkeleton(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	ofPushStyle();
	for(int j = 0; j < kinect->SKELETON_POSITION_COUNT; j++) {
				s	<< j << "     "
					<< kinect->skeletonPoints[updateActivePlayer()][j].x << "     "
					<< kinect->skeletonPoints[updateActivePlayer()][j].y << "     "
					<< kinect->skeletonPoints[updateActivePlayer()][j].z << "     \n";
			
				ofSetColor(255,0,0);
				ofCircle(getRawJoint(FIRST_ACTIVE,j),10);
				ofSetColor(0,255,130);
				ofCircle(getMappedJoint(FIRST_ACTIVE,j),10);
				ofSetColor(1,0,130);
				ofCircle(getSkeletonJoint(FIRST_ACTIVE,j),10);
			

	}
	ofSetColor(0,0,0);
	ofDrawBitmapString(s.str(),10,10);
	ofPopStyle();


	




}


void   Kinect440::drawDefaultDebugScreen() {
	
	
	// Draw video only
	if(bDrawVideo){
		// draw video images from kinect camera
		kinect->drawVideo(0, 0, 1024, 768);
	// Draw depth + users label only
	}else if(bDrawDepthLabel){
		ofEnableAlphaBlending();

		// draw depth images from kinect depth sensor
		kinect->drawDepth(0, 0, 1024, 768);
		// draw players' label images on video images
		kinect->drawLabel(0, 0, 1024, 768);
		ofDisableAlphaBlending();
	// Draw skeleton only
	}else if(bDrawSkeleton){
		kinect->drawSkeleton(0, 0, 1024, 768);	// draw skeleton images on video images
	// Draw calibrated image only
	}else{
		if(!bPlayback){
			// draw video images from kinect camera
			kinect->drawVideo(20, 20, 400, 300);
			ofEnableAlphaBlending();
			// draw depth images from kinect depth sensor
			kinect->drawDepth(450, 20, 400, 300);
			// draw players' label images on video images
			kinect->drawLabel(450, 20, 400, 300);
			ofDisableAlphaBlending();
			// draw skeleton images on video images
			kinect->drawSkeleton(20, 20, 400, 300);

		}else{
			kinectPlayer.draw(20, 20, 400, 300);
			ofEnableAlphaBlending();
			kinectPlayer.drawDepth(20, 340, 400, 300);
			kinectPlayer.drawLabel(20, 340, 400, 300);

			ofDisableAlphaBlending();
			kinectPlayer.drawSkeleton(20, 20, 400, 300);
		}
	}

	ofPushMatrix();
	ofTranslate(35, 35);
	ofFill();
	if(bRecord) {
		ofSetColor(255, 0, 0);
		ofCircle(0, 0, 10);
	}
	if(bPlayback) {
		ofSetColor(0, 255, 0);
		ofTriangle(-10, -10, -10, 10, 10, 0);
	}
	ofPopMatrix();

	stringstream kinectReport;
	if(bPlugged && !kinect->isOpened() && !bPlayback){
		ofSetColor(0, 255, 0);
		kinectReport << "Kinect is plugged..." << endl;
		ofDrawBitmapString(kinectReport.str(), 200, 300);
	}else if(!bPlugged){
		ofSetColor(255, 0, 0);
		kinectReport << "Kinect is unplugged..." << endl;
		ofDrawBitmapString(kinectReport.str(), 200, 300);
	}
}

void   Kinect440::exit() {
	if(calibratedTexture.bAllocated()){
		calibratedTexture.clear();
	}

	if(videoDraw_) {
		videoDraw_->destroy();
		videoDraw_ = NULL;
	}
	if(depthDraw_) {
		depthDraw_->destroy();
		depthDraw_ = NULL;
	}
	if(labelDraw_) {
		labelDraw_->destroy();
		labelDraw_ = NULL;
	}
	if(skeletonDraw_) {
		delete skeletonDraw_;
		skeletonDraw_ = NULL;
	}

	kinect->setAngle(0);
	kinect->close();
	kinect->removeKinectListener(this);
	kinectPlayer.close();
	kinectRecorder.close();

}

void Kinect440::kinectPlugged() {
	bPlugged = true;
}

void Kinect440::kinectUnplugged() {
	bPlugged = false;
}

void   Kinect440::startRecording(){
	if(!bRecord){
		// stop playback if running
		stopPlayback();

		kinectRecorder.setup(*kinect, "recording.dat");
		bRecord = true;
	}
}


void   Kinect440::startPlayback(){
	if(!bPlayback){
		stopRecording();
		kinect->close();

		// set record file and source
		kinectPlayer.setup("recording.dat");
		kinectPlayer.loop();
		kinectPlayer.play();
		kinectSource = &kinectPlayer;
		bPlayback = true;
	}
}

void   Kinect440::stopPlayback(){
	if(bPlayback){
		kinectPlayer.close();
		kinect->open();
		kinectSource = kinect;
		bPlayback = false;
	}
}

void   Kinect440::stopRecording(){
	if(bRecord){
		kinectRecorder.close();
		bRecord = false;
	}
}

ofPoint Kinect440::getSkeletonJoint(int player,int joint){

	if(player == FIRST_ACTIVE){
		player = updateActivePlayer();
	}

	//Sanity Check
	if(player > ofxKinectNui::SKELETON_COUNT || joint > ofxKinectNui::SKELETON_POSITION_COUNT || player < 0 || joint < 0 ) {
	
		printf("440 [WARNING] getSkeletonPoint: Attempting to get a player or index greater than the possible maximum or less than zero. Player = %i; joint = %i ; Returning (0,0)\n",player,joint);

		return ofPoint(0,0);
	
	}else {

		return skeletonLerpModel[player][joint];
	}
}

ofPoint Kinect440::getMappedJoint(int player,int joint){

	if(player == FIRST_ACTIVE){
		player = updateActivePlayer();
	}

	//Sanity Check
	if(player > ofxKinectNui::SKELETON_COUNT || joint > ofxKinectNui::SKELETON_POSITION_COUNT || player < 0 || joint < 0 ) {
	
		printf("440 [WARNING] getMappedRawPoint: Attempting to get a player or index greater than the possible maximum or less than zero. Player = %i; joint = %i ; Returning (0,0)\n",player,joint);

		return ofPoint(0,0);
	
	}else {

		ofPoint p;

		p.x = ofMap(kinect->skeletonPoints[player][joint].x,0,320,0,ofGetWindowWidth());
		p.y = ofMap(kinect->skeletonPoints[player][joint].y,0,240,0,ofGetWindowHeight());

		return p;
	}
}

ofPoint Kinect440::getRawJoint(int player,int joint){


	if(player == FIRST_ACTIVE){
		player = updateActivePlayer();
	}

	//Sanity Check
	if(player > ofxKinectNui::SKELETON_COUNT || joint > ofxKinectNui::SKELETON_POSITION_COUNT || player < 0 || joint < 0 ) {
	
		printf("440 [WARNING] getMappedRawPoint: Attempting to get a player or index greater than the possible maximum or less than zero. Player = %i; joint = %i ; Returning (0,0)\n",player,joint);

		return ofPoint(0,0);
	
	}else {


		ofPoint p;

		p.x = kinect->skeletonPoints[player][joint].x;
		p.y = kinect->skeletonPoints[player][joint].y;
		return p;
	}

}


int Kinect440::updateActivePlayer() {
	
	for(int i = 0; i < ofxKinectNui::SKELETON_COUNT; i++) {

		if(kinect->skeletonPoints[i][0].z > 0){
			
			return i;

		}

	}

	return 0;

}