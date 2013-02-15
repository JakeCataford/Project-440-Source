#pragma once

#include "IVisualiserBase.h"
#include "ofMain.h"
#include "Kinect440.h"
#include "Audio440.h"

class PulseOrb : public VisualiserBase {

	///This visualiser pulses a giant ball, mostly for testing...
public:

	//Implement and overrride virtuals


	PulseOrb() : isClean(false),
		isOutro(false),
		isIntro(false),
		kinect(NULL),
		audio(NULL),
		counter(0),
		introMultip(0)
	{};

	~PulseOrb(){};

	void init(Audio440&, /*ColorTheme,*/ Kinect440& ); //Setup vars and refs and such
	void queueIntro(); //Switch on the boolean to start and set up initial vals
	void draw(); //Standard draw loop (also draws intro and outro, use conditionals)
	void update(); //Update data, happens before draw
	void queueOutro(); //Switch outro bool
	void cleanup(); //Cleanup memory and flip cleanup state
	bool getCleanupState(); //return a value that specifies the cleanup is over


private:

	Kinect440 * kinect;
	Audio440 * audio;

	float counter;

	float introMultip;

	bool isClean;
	bool isIntro;
	bool isOutro;

};