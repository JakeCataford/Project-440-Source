#pragma once
#include "ofMain.h"

class ColorTheme
{
public:
	ColorTheme(void);
	~ColorTheme(void);

	void newTheme();
	void ctFadeOut();

	ofColor getBaseColor();
	ofColor getLightColor();
	ofColor getDarkColor();
	ofColor getCompColor();

	ofColor color1;
	ofColor color2;
	ofColor color3;
	ofColor color4;
};

