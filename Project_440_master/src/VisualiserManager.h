#pragma once
#include "Kinect440.h"
#include "ofMain.h"
#include "Audio440.h"
#include "IVisualiserBase.h"
#include "VCR.h"
#include "Tunnel.h"
#include "Idle.h"
#include "Midi.h"
#include "Fireflies.h"

class VisualiserManager {

public:
	VisualiserManager(){};
	~VisualiserManager(){};


	void init(Audio440&,Kinect440&);
	void cycle();
	void draw();
	void update();
	vector <VisualiserBase*> visualiserPtrs;

	//references
	Audio440* aud;
	Kinect440 * kin;
	Midi * midi;

	ColorTheme theme;
	//Visualisers
	VCR vcr;
	Tunnel tunnel;
	Idle idle;
	Fireflies flies;

	int current;
	int previous;


};