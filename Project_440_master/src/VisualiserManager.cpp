#include "VisualiserManager.h"

void VisualiserManager::init(Audio440& audio,Kinect440& kinect) {

	aud = &audio;
	kin = &kinect;
	theme = ColorTheme();
	theme.newTheme();
	vcr = VCR();
	tunnel = Tunnel();
	flies = Fireflies();
	idle = Idle();
	heiro = Heiroglyphs();
	idle.init(audio,kinect,theme);
	vcr.init(audio,kinect,theme);
	tunnel.init(audio,kinect,theme);
	flies.init(audio,kinect,theme);
	heiro.init(audio,kinect,theme);
	intro = &idle;
	visualiserPtrs.push_back(&tunnel);
	visualiserPtrs.push_back(&vcr);
	visualiserPtrs.push_back(&flies);
	visualiserPtrs.push_back(&heiro);
	current = 0;
	previous = visualiserPtrs.size() - 1;

	for(int i = 0; i < visualiserPtrs.size(); i++){
		visualiserPtrs[i]->queueIntro();
		visualiserPtrs[i]->update();
		visualiserPtrs[i]->draw();
		visualiserPtrs[i]->queueOutro();
	}
	intro->queueIntro();
	del = Delauney440();
	playerTimeout = 100;
}

void VisualiserManager::reset() {

	isReset = true;

}

void VisualiserManager::cycle() {

	if(isReset) {
		isReset = false;
		playerTimeout = 100;
	}

	theme.newTheme();
	
	current++;
	if(current >= visualiserPtrs.size()){
		current = 0;
	}

	previous = current - 1;

	if(previous < 0){
		previous = visualiserPtrs.size() -1;
	}

	

	visualiserPtrs[current]->queueIntro();
	visualiserPtrs[previous]->queueOutro();

	printf("%i, %i, Size: %i ",current,previous,visualiserPtrs.size());

}

void VisualiserManager::draw() {

	if(isReset) {

		intro->draw();

	}else{

	if(!visualiserPtrs[previous]->getCleanupState()){
		visualiserPtrs[previous]->draw();
	}

	visualiserPtrs[current]->draw();
	}

	if(!kin->isPlayerActive()) {
		playerTimeout--;
	}else{
		if(isReset) {
			//play
			
		}
		playerTimeout = 100;
	}
	ofPushStyle();
	//del.update(kin->getContourPoly(),aud->getAvgBin(7)*25);
	ofPopStyle();

}

void VisualiserManager::update() {

	if(playerTimeout < 0){

		isReset = true;

	}

	visualiserPtrs[current]->update();

	if(!visualiserPtrs[previous]->getCleanupState()){
		visualiserPtrs[previous]->update();
	}

	
	

}