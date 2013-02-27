#pragma once

#include "ofGraphics.h"
#include "ofMain.h"
#include "ColorTheme.h"

class pEllipse
{
public:
	pEllipse(float pSize, ColorTheme &curTheme);
	~pEllipse(void);

	void update();
	void draw(float pSize);

	float px, py, pWidth, pHeight;
	ofPoint position;
	ofPoint speed;
	float pxD, pyD;
	float prevW, prevH;
	ColorTheme * colorTheme;
	float counter;
};

