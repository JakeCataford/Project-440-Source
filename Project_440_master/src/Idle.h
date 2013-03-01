#pragma once
#include "Kinect440.h"
#include "ColorTheme.h"
#include "Audio440.h"
#include "Scanlines.h"
#include "IVisualiserBase.h"



class Idle : public VisualiserBase{

public:

	Idle(){};
	~Idle(){};

	void init(Audio440&,Kinect440&, ColorTheme&); //Setup vars and refs and such
	void queueIntro(); //Switch on the boolean to start and set up initial vals
	void draw(); //Standard draw loop (also draws intro and outro, use conditionals)
	void update(); //Update data, happens before draw
	void queueOutro(); //Switch outro bool
	bool getCleanupState(); //return a value that specifies the cleanup is over
	
	
private:

	Kinect440 * kinect;
	Audio440 * audio;
	ColorTheme * theme;


	Scanlines scan;
	float age;
	float lastAmp;
	
	ofTrueTypeFont myfont;


	float intro;
	ofFbo fbo;
	ofImage flash;
	ofPoint sph;
	bool isOutro;
	bool isCleanup;
	ofShader shader;
	ofShader abr;
	ofFbo abrfbo;

	
};