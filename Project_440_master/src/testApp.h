
#pragma once
#include "ofxKinectNui.h"
#include "Kinect440.h"
#include "ofMain.h"
#include "Midi.h"

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
		
		ofxKinectNui kinref;


		//Core Classes

		Kinect440 kinect;
		Midi midi;

		//Debug
		bool midiDebug;
		bool skeletonDebug;
		bool videoColorDebug;


};
