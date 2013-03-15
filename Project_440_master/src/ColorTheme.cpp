#include "ColorTheme.h"

//----------------------------------------------------------------------------------
ColorTheme::ColorTheme(void)
{
}

//----------------------------------------------------------------------------------
ColorTheme::~ColorTheme(void)
{
}

//----------------------------------------------------------------------------------
void ColorTheme::ctFadeOut()
{
	//when the color theme swtiches, it'll need to fade out then be reset
	color1.setBrightness(color1.getBrightness() * 0.9);
	color2.setBrightness(color2.getBrightness() * 0.9);
	color3.setBrightness(color3.getBrightness() * 0.9);
	color4.setBrightness(color4.getBrightness() * 0.9);
}

//----------------------------------------------------------------------------------
void ColorTheme::newTheme()
{
	color1 = ofColor::fromHsb(ofRandom(0,255),ofRandom(20,255),ofRandom(100,255));

	color2 = ofColor::fromHsb(color1.getHue()*0.9,color1.getSaturation()*0.4,color1.getBrightness());

	float complement = color1.getHue() + ofRandom(-50, 50);

	if(complement+127.5 > 255){
		complement = (complement+127.5) - 255;
	}else{
		complement = color1.getHue() + 127.5;
	}

	color3 = ofColor::fromHsb(complement,color1.getSaturation(),color1.getBrightness());	

	color4 = ofColor::fromHsb(color1.getHue(),color1.getSaturation(),color1.getBrightness()*0.8);
}

//----------------------------------------------------------------------------------
ofColor ColorTheme::getBaseColor(){
	//return the base color
	return color1;
}

//----------------------------------------------------------------------------------
ofColor ColorTheme::getLightColor(){
	//return the lighter version of the base color
	return color2;
}

//----------------------------------------------------------------------------------
ofColor ColorTheme::getDarkColor(){
	//return the darker version of the base color
	return color4;
}

//----------------------------------------------------------------------------------
ofColor ColorTheme::getCompColor(){
	//return the base color's complimentary color
	return color3;
}
