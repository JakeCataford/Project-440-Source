#pragma once
#include "Kinect440.h"
#include "ofMain.h"
#include "Audio440.h"
#include "IVisualiserBase.h"
#include "Scanlines.h"

class TunnelParticle{
public:
	TunnelParticle(float x,float y, float z, float sx, float sy, float sz) : age(1) {
		position = ofVec3f(x,y,z);
		speed = ofVec3f(sx,sy,sz);
	
	};
	~TunnelParticle(){};

	void update() {

		position += speed;

		age++;
	};

	void draw(float amp) {
		ofPushMatrix();
		ofPushStyle();
		ofSetColor(255,255,255);
		ofTranslate(position);
		ofSphere(amp);
		ofPopStyle();
		ofPopMatrix();

	}
	float age;
	ofPoint position;
	ofVec3f speed;
};


class Tunnel : public VisualiserBase {

public:
	Tunnel() : isCleanup(false),isIntro(false),introCounter(0),isOutro(false){};
	~Tunnel(){};
	void init(Audio440&,Kinect440&); //Setup vars and refs and such
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
	ofShader basic;
	ofMesh mesh;
	float age;
	bool isCleanup;
	bool isIntro;
	bool isOutro;
	int introCounter;
	ofFbo tunnel;
	ofCamera camera;
	int prevamp;
	float offset;
	ofShader bulge;
	Scanlines scan;
	ofImage flash;
	vector <TunnelParticle> parts;
	ofLight light;
};