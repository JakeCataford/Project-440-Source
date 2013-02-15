#pragma once
#include "Kinect440.h"
#include "Audio440.h"

class VisualiserBase {

public:

	VisualiserBase(){};
	~VisualiserBase(){};

	void init(Audio440&,Kinect440&); //Setup vars and refs and such
	void queueIntro(); //Switch on the boolean to start and set up initial vals
	void draw(); //Standard draw loop (also draws intro and outro, use conditionals)
	void update(); //Update data, happens before draw
	void queueOutro(); //Switch outro bool
	void cleanup(); //Cleanup memory and flip cleanup state
	bool getCleanupState(); //return a value that specifies the cleanup is over

	
};