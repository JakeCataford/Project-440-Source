#include "VisualiserManager.h"

void VisualiserManager::init(Audio440& audio, Kinect440& kinect) {
	
	
	aud = &audio;
	kin = &kinect;

	vcr = VCR();
	tunnel = Tunnel();
	vcr.init(audio,kinect);
	tunnel.init(audio,kinect);
	visualiserPtrs.push_back(&tunnel);
	visualiserPtrs.push_back(&vcr);
	current = 0;
	previous = visualiserPtrs.size() - 1;

}

void VisualiserManager::cycle() {


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

	

	if(!visualiserPtrs[previous]->getCleanupState()){
		visualiserPtrs[previous]->draw();
	}

	visualiserPtrs[current]->draw();


}

void VisualiserManager::update() {

	visualiserPtrs[current]->update();

	if(!visualiserPtrs[previous]->getCleanupState()){
		visualiserPtrs[previous]->update();
	}

}