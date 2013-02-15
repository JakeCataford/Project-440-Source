#pragma once

#include "ofMain.h"
#include "fft.h"
#define BUFFER_SIZE 512
#define NUM_WINDOWS 80
#define NUM_OF_AVG 25
class Audio440 {

	public:

		static const int LEFT = 1;
		static const int RIGHT = 2;
		static const int MIX = 0;

		Audio440(){};
		~Audio440(){};

		void init();
		void update();

		//Hooks
		float getRawAmp();
		float getAmp();
		float getAvgBin(int);
		//Debug
		void drawAudioDebug();


		//FFT bins
		float* left;
		float* right;

		int 	bufferCounter;
		fft		myfft;
		
		float magnitude[BUFFER_SIZE];
		float phase[BUFFER_SIZE];
		float power[BUFFER_SIZE];
		
		float freq[NUM_WINDOWS][BUFFER_SIZE/2];
		float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];
		float logAvgBins[NUM_OF_AVG];

		float softMagnitude[BUFFER_SIZE];
		float rawAmp;
		float* audioInput;

		float softAmplitude;
		float subs;


};

