#pragma once
#include "Kinect440.h"
#include "ofMain.h"
#include "Audio440.h"
#include "IVisualiserBase.h"
#include "VCR.h"
#include "Tunnel.h"
#include "Tree.h"

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


	ColorTheme theme;
	//Visualisers
	VCR vcr;
	Tunnel tunnel;
	Tree tree;

	int current;
	int previous;


};