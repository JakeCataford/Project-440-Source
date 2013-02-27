#pragma once
#include "Kinect440.h"
#include "Visualizer.h"
#include "ofMain.h"
#include "pEllipse.h"
#include "Audio440.h"

class Vis_Circles {
public:
	Vis_Circles(void);
	~Vis_Circles(void);

	void init(Audio440&, ColorTheme&, Kinect440& ); //Setup vars and refs and such
	void queueIntro(); //Switch on the boolean to start and set up initial vals
	void draw(); //Standard draw loop (also draws intro and outro, use conditionals)
	void update(); //Update data, happens before draw
	void queueOutro(); //Switch outro bool
	void cleanup(); //Cleanup memory and flip cleanup state
	bool getCleanupState(); //return a value that specifies the cleanup is over

	vector<pEllipse> myParts;
	int specSize;
	ofSoundPlayer song;
	float pHue, pSat, pBri;
	float* val;

	//References
	Kinect440* kinect;
	Audio440* audio;
	ColorTheme* cTheme;
	float counter;
};

