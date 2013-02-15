
#pragma once
#include "ofxKinectNui.h"
#include "Kinect440.h"
#include "ofMain.h"
#include "Midi.h"
#include "Audio440.h"
#include "PulseOrb.h"

class testApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();

		

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void audioIn(float *, int, int);
		//references
		ofxKinectNui kinref;
		//Core Classes
		Audio440 audio;
		Kinect440 kinect;
		Midi midi;

		//Debug
		bool midiDebug;
		bool skeletonDebug;
		bool videoColorDebug;
		bool audioDebug;
		bool frameRateDebug;

		//test
		PulseOrb orb;
};
