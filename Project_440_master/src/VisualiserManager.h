#pragma once
#include "Kinect440.h"
#include "ofMain.h"
#include "Audio440.h"
#include "IVisualiserBase.h"
#include "VCR.h"
#include "Tunnel.h"
#include "Idle.h"
#include "Heiroglyphs.h"
#include "Fireflies.h"
#include "Delauney.h"

class VisualiserManager {

public:
	VisualiserManager() :
	isReset(true),
	playerTimeout(0)
	{};
	~VisualiserManager(){};


	void init(Audio440&,Kinect440&);
	void cycle();
	void draw();
	void update();
	void reset();
	vector <VisualiserBase*> visualiserPtrs;

	VisualiserBase * intro;

	//references
	Audio440* aud;
	Kinect440 * kin;

	ColorTheme theme;
	//Visualisers
	VCR vcr;
	Tunnel tunnel;
	Idle idle;
	Fireflies flies;
	Heiroglyphs heiro;
	int playerTimeout;
	Delauney440 del;
	bool isReset;

	int current;
	int previous;


};