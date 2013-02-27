#pragma once
#include "Kinect440.h"
#include "ofMain.h"
#include "ColorTheme.h"
#include "Audio440.h"
#include "IVisualiserBase.h"
#include "Scanlines.h"



class Tree : public VisualiserBase {

public:
	Tree() : isCleanup(false),isIntro(false),introCounter(0),isOutro(false){};
	~Tree(){};
	void init(Audio440&,Kinect440&,ColorTheme&); //Setup vars and refs and such
	void queueIntro(); //Switch on the boolean to start and set up initial vals
	void draw(); //Standard draw loop (also draws intro and outro, use conditionals)
	void update(); //Update data, happens before draw
	void queueOutro(); //Switch outro bool
	bool getCleanupState(); //return a value that specifies the cleanup is over
	void generate();

private: 
	ofVec3f direction;
	Kinect440* kinect;
	Audio440* audio;
	ColorTheme * theme;
	ofShader basic;
	ofMesh mesh;
	float age;
	bool isCleanup;
	bool isIntro;
	bool isOutro;
	int introCounter;
	ofFbo fbo;
	ofCamera camera;
	int prevamp;
	float offset;
	ofShader bulge;
	Scanlines scan;
	ofImage flash;
	ofLight light;
	ofEasyCam cam;
};