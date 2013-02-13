#include "ofMain.h"


class Audio440 {

	public:

		static const int LEFT = 1;
		static const int RIGHT = 2;
		static const int MIX = 0;

		Audio440(){};
		~Audio440(){};

		void init();

		//Hooks
		float getRawAverageAmp(int);

		//Debug
		void drawAudioDebug();

		//fSoundStream stream;

		float left[512];
		float right[512];



};

