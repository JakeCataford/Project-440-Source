#pragma once

#include "Kinect440.h"
#include "ofMain.h"
#include "poly2tri\poly2tri.h"
#include "audio440.h"

class Wireframe {


public:
	Wireframe(){};
	~Wireframe(){};

	void init(Kinect440 & ref, Audio440 & aud);

	void clearPointers();

	void draw();
	

	Kinect440 * kinect;
	Audio440 * audio;

	vector <p2t::Point *> polyline;
};