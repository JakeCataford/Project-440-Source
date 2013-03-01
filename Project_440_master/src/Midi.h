#pragma once
#include "Kinect440.h"
#include "ofMain.h"
#include "ofxMidi.h"


class Midi {

public:
	Midi(){};
	~Midi();

	Kinect440* kinect; 

	void init(Kinect440&);
	void update();

	//Setters
	void setControllerValue(int controller, float value);
	
	//Song Manipulations
	void advanceSongState();//TODO
	void resetSong();//TODO
	void interuptSongReset();//TODO
	
	//Getters
	float getMidiTempo();//TODO

	//Debug
	void drawDebugScreen(bool);
	void debugUpdate();

private:

	bool bDebugMode;

	ofxMidiOut midiOut;
	int channel;
	
	unsigned int currentPgm;
	int note, velocity;
	int controllers[64];
	int cycler;

};