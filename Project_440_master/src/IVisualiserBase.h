#pragma once
#include "Kinect440.h"
#include "Audio440.h"

class VisualiserBase {

public:

	VisualiserBase(){};
	~VisualiserBase(){};

	virtual void init(Audio440&,Kinect440&){}; //Setup vars and refs and such
	virtual void queueIntro(){}; //Switch on the boolean to start and set up initial vals
	virtual void draw(){}; //Standard draw loop (also draws intro and outro, use conditionals)
	virtual void update(){}; //Update data, happens before draw
	virtual void queueOutro(){}; //Switch outro bool
	virtual bool getCleanupState(){return false;}; //return a value that specifies the cleanup is over

	
};