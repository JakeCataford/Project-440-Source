#pragma once

#include "ofGraphics.h"
#include "ColorTheme.h"

class Visualizer
{
public:
	Visualizer(void);
	~Visualizer(void);

protected:

	//variables
	int nBandsToGet;
	int decayTimer;
	char visualizerID;

};

