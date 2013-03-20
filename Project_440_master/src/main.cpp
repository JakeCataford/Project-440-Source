
#include "testApp.h"
#include "ofMain.h"
#include "ofAppGlutWindow.h"



//========================================================================
int main( ){

    ofAppGlutWindow window;

	window.setGlutDisplayString("rgb alpha double samples depth");

	//ofSetupOpenGL(&window, 2650,1440, OF_FULLSCREEN);		
    ofSetupOpenGL(&window, 1920,1080, OF_FULLSCREEN);	// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
