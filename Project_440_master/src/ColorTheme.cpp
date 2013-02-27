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
	color1 = ofColor::fromHsb(ofRandom(255),ofRandom(100,200),255);

	color2 = ofColor::fromHsb(color1.getHue()*0.9,color1.getSaturation(),200);

	float complement = color1.getHue();
	if(complement+127.5 > 255){
		complement = (complement+127.5) - 255;
	}else{
		complement = color1.getHue() + 127.5;
	}

	color3 = ofColor::fromHsb(complement,color1.getSaturation(),255);

	color4 = ofColor::fromHsb(color1.getHue(),color1.getSaturation()-60,100);
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
