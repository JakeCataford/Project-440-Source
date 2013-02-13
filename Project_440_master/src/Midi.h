#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class Midi {

public:
	Midi(){};
	~Midi();

	void init();

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

private:

	

	ofxMidiOut midiOut;
	int channel;
	
	unsigned int currentPgm;
	int note, velocity;
	int controllers[64];
	int cycler;

};