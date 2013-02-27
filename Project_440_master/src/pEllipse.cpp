#include "pEllipse.h"


pEllipse::pEllipse(float pSize, ColorTheme &curTheme)
{

	colorTheme = &curTheme;

	position = ofPoint(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
    pWidth = pSize;
    pHeight = pSize;
    speed = ofPoint(ofRandom(-8,8),ofRandom(-8,8));
    prevW = 0;
    prevH = 0;
}


pEllipse::~pEllipse(void)
{
}

void pEllipse::update()
{
	if (position.x < 0) speed.x *= -1;
    else if (position.x > ofGetWidth()*1.5) speed.x *= -1;
    else if (position.y < 0) speed.y *= -1;
    else if (position.y > ofGetHeight()*1.5) speed.y *= -1;

    position.x += speed.x;
    position.y += speed.y;
	position.z = sin(counter)*200;
	counter+=0.001;
}

void pEllipse::draw(float pSize) {
	pSize *= 9;
    if (pSize > 2.0) {
		//do background change
	}

	/*
	float h = 0;
	float s = 255;
	float b = (pSize*255/2.5);
	ofColor color1 = ofColor::fromHsb(h,s,b);
	*/

	float h = colorTheme->color1.getHue();
	float s = colorTheme->color1.getSaturation();
	float b = colorTheme->color1.getBrightness();
	ofColor color1 = ofColor::fromHsb(h,s,b);

	ofSetColor(color1);
    ofFill();

    if (pSize > prevW*1.5) {
	 
	  ofSphere(position, prevW + 0.75*(pSize - prevW));
	  prevW = pSize;
      prevH = pSize;
    }
    else {
	  
	  ofSphere(position, (prevW)*0.95);
      prevW = prevW*0.95;
      prevH = prevH*0.95;
    }

	
}