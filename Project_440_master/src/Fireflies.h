#pragma once
#include "Kinect440.h"
#include "ColorTheme.h"
#include "Audio440.h"
#include "Scanlines.h"
#include "IVisualiserBase.h"


/******** CREATE PARTICLE CLASS ***********/
class pEllipse
{
public:
	/********** CONSTRUCTOR **********/
	pEllipse(float pSize, ColorTheme &curTheme){
		colorTheme = &curTheme;

		px = rand() % ofGetWidth();
		py = rand() % ofGetHeight();
		pWidth = pSize;
		pHeight = pSize;
		pxD = ofRandom(-4, 4);
		pyD = ofRandom(-4, 4);
		prevW = 0;
		prevH = 0;
		colorChoice = ofRandom(0,1);
	};

	/********** DECONSTRUCTOR **********/
	~pEllipse(void){};

	/********** UPDATE **********/
	void update(){
		if (px < 0){ pxD *= -1; px = 0;}
		else if (px > ofGetWidth() + 100){ pxD *= -1; px = ofGetWidth();}
		else if (py < 0){ pyD *= -1; py = 0;}
		else if (py > ofGetHeight()){ pyD *= -1; py = ofGetHeight();}

		px += pxD;
		py += pyD;
	};

	/********** DRAW **********/
	void draw(float pSize){
		float inflation = 10;

		float h1, h2, s1, s2, b1, b2 = 0.0;

		if(colorChoice<0.5){
			h1 = colorTheme->color1.getHue();
			s1 = colorTheme->color1.getSaturation();
			b1 = colorTheme->color1.getBrightness();
		}else{
			h1 = colorTheme->color3.getHue();
			s1 = colorTheme->color3.getSaturation();
			b1 = colorTheme->color3.getBrightness();
		}

		ofColor color1 = ofColor::fromHsb(h1, s1, b1, 200);

		ofSetColor(color1);
		ofFill();

		if (pSize*inflation > prevW*1.5) {
			pSize *= inflation;
			ofPoint tempPoint = ofPoint(px, py);
			ofSphere(tempPoint,pSize);
			prevW = pSize;
			prevH = pSize;
		}else {
			ofPoint tempPoint = ofPoint(px, py);
			ofSphere(tempPoint, prevW*0.95);
			prevW = prevW*0.95;
			prevH = prevH*0.95;
		}
	};

	/********** EXPLODE **********/
	void explode(float amp){
		px = px + ofRandom(-amp, amp);
		py = py + ofRandom(-amp, amp);
	};

	/********** IMPLODE **********/
	void implode(float amp){
		if(px < (ofGetWidth()/2)){
			px = px + ((ofGetWidth()/2) - px)*amp;
		}else{
			px  = px - (px - (ofGetWidth()/2))*amp;
		}

		if(py < (ofGetHeight()/2)){
			py = py + ((ofGetHeight()/2) - py)*amp;
		}else{
			py  = py - (py - (ofGetHeight()/2))*amp;
		}
	};

	/********** VARIABLES **********/
	float px, py, pWidth, pHeight;
	float pxD, pyD;
	float prevW, prevH;
	ColorTheme * colorTheme;
	float colorChoice;
};

class Fireflies :
	public VisualiserBase
{
public:
	Fireflies(void);
	~Fireflies(void);

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

	float intro;
	ofPoint sph;
	bool isOutro;
	bool isCleanup;
	float age;
	float lastAmp;

	vector<pEllipse> myParts;
	int specSize;
	float pHue, pSat, pBri;
	float* val;
	ColorTheme * cTheme;
	ofFbo fbo;
	ofShader bulge;
	Scanlines scan;
	ofImage flash;

	ofShader abr;
	ofFbo abrFbo;

	float bandAverage, prevBandAverage;
};

