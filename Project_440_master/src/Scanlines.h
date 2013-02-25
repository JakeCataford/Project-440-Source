#pragma once
#include "ofMain.h"

class Scanlines {

	// feathered scanlines, like on an old crt display...
public:

	Scanlines();
	~Scanlines(){};

	void draw();
	void update(float amp);

	

private:

	float opacity;
	ofFbo texture;
	float age;
	static const int SCANLINE_HEIGHT = 5;
	static const int SCANLINE_SPACING = 5;
	ofImage feather;

};