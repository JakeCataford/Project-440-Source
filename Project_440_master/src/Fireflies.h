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
	pEllipse(float pSize, ColorTheme &curTheme, Kinect440& kin, ofImage& sprite){
		colorTheme = &curTheme;
		circle = &sprite;
		kinect = &kin;
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
	void update(float pSize){


		if (px < 0){ pxD *= -1; px = 0;}
		else if (px > ofGetWidth() + 100){ pxD *= -1; px = ofGetWidth();}
		else if (py < 0){ pyD *= -1; py = 0;}
		else if (py > ofGetHeight()){ pyD *= -1; py = ofGetHeight();}

		ofPoint pointLeftHand = kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE, NUI_SKELETON_POSITION_HAND_LEFT);
		ofPoint pointRightHand = kinect->getSkeletonJoint(Kinect440::FIRST_ACTIVE, NUI_SKELETON_POSITION_HAND_RIGHT);

		ofVec2f forceLeft = ofVec2f((pointLeftHand.x - px), (pointLeftHand.y - py));
		ofVec2f forceRight = ofVec2f((pointRightHand.x - px), (pointRightHand.y - py));
		
		forceLeft = forceLeft.normalize();
		forceRight = forceRight.normalize();

		if(abs(ofDist(pointLeftHand.x, pointLeftHand.y, px, py)+1) < 800){
			forceLeft *= ((1/abs(ofDist(pointLeftHand.x, pointLeftHand.y, px, py))+1)*1200)/abs(ofDist(pointLeftHand.x, pointLeftHand.y, px, py)+1);
			
			px -= forceLeft.x;
			py -= forceLeft.y;
		}

		if(abs(ofDist(pointRightHand.x, pointRightHand.y, px, py)+1) < 800){
			forceRight *= ((1/abs(ofDist(pointRightHand.x, pointRightHand.y, px, py))+1)*1200)/abs(ofDist(pointRightHand.x, pointRightHand.y, px, py)+1);
		
			px -= forceRight.x;
			py -= forceRight.y;
		}

		px += pxD;

		py += pyD;
	};

	/********** DRAW **********/
	void draw(float pSize){
		float inflation = 10;

		float h1, h2, s1, s2, b1, b2 = 0.0;

		if(colorChoice<0.5){
			ofSetColor(colorTheme->color1.r,colorTheme->color1.g,colorTheme->color1.b,200);
		}else{
			ofSetColor(colorTheme->color3.r,colorTheme->color3.g,colorTheme->color3.b,200);
		}

		

		
		ofSetCircleResolution(100);
		if (pSize*inflation > prevW*1.5) {
			pSize *= inflation;
			ofPoint tempPoint = ofPoint(px, py);
			circle->draw(tempPoint.x,tempPoint.y,pSize,pSize);
			prevW = pSize;
			prevH = pSize;
		}else {
			ofPoint tempPoint = ofPoint(px, py);
			circle->draw(tempPoint.x,tempPoint.y,prevW*0.95,prevW*0.95);
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
	ofImage * circle;
	Kinect440 * kinect;
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
	ofImage circle;
	ofShader abr;
	ofFbo abrFbo;

	float rangeX, rangeY, kinectHandSize;
	ofPoint pointLeftHand, pointRightHand, pointHead;

	float bandAverage, prevBandAverage;
};

