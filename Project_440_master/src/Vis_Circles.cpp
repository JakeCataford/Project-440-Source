#include "Vis_Circles.h"

//----------------------------------------------------------------------------------
Vis_Circles::Vis_Circles(void)
{
}

//----------------------------------------------------------------------------------
Vis_Circles::~Vis_Circles(void)
{
}

//----------------------------------------------------------------------------------
void Vis_Circles::init(Audio440& aud,ColorTheme& curTheme,Kinect440& kin)
{
	cTheme = &curTheme;
	kinect = &kin;
	audio = &aud;

	counter = 0;
	float size = 0;
	for (int i = 0;i < 255; i++){
		size = audio->getAvgBin(i%13);
		pEllipse pe(audio->getAvgBin(i%13), *cTheme);
		myParts.push_back(pe);
	}
}

//----------------------------------------------------------------------------------
void Vis_Circles::update()
{

}

//----------------------------------------------------------------------------------
void Vis_Circles::draw()
{


	ofPushView();

	ofPushMatrix();
	ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
	ofRotateX(sin(counter)*20);
	ofRotateY(sin(counter*2)*20);
	ofTranslate(-ofGetWidth()/2,-ofGetHeight()/2);
	//ofPushMatrix();

	//update background color
	ofClear(cTheme->color3);



	ofPushStyle();
	for (int i = 0; i < 255; i++)
	{   
		myParts[i].update();
		myParts[i].draw(audio->getAvgBin(i));
	}
	counter+= 0.01;
	//ofPopMatrix();
	ofPopMatrix();
	ofPopStyle();
	ofPopView();
	
}

//----------------------------------------------------------------------------------
void Vis_Circles::cleanup()
{
	
}

bool Vis_Circles::getCleanupState() {
	return false;
}

//----------------------------------------------------------------------------------
void Vis_Circles::queueIntro()
{
	
}

//----------------------------------------------------------------------------------
void Vis_Circles::queueOutro()
{
	
}
