#pragma once
#define NO_KINECT_DEBUG false
#include "ofxKinectNui.h"

//#include "ofMain.h"
#include "ofxKinectNuiPlayer.h"
#include "ofxKinectNuiRecorder.h"


using namespace std;

class ofxKinectNuiDrawTexture;
class ofxKinectNuiDrawSkeleton;

class Kinect440 {


	// BIG TODO: Handle players

public:

	static const int FIRST_ACTIVE = 10;

	Kinect440(){};
	~Kinect440(){};
	void init(ofxKinectNui&);
	void update();
	void drawDefaultDebugScreen();
	void drawVelocityDebug();
	void drawSkeletonDebugScreen();
	void exit();

	void kinectPlugged();
	void kinectUnplugged();
		
	void startRecording();
	void stopRecording();
	void startPlayback();
	void stopPlayback();

	//hooks, for skeleton use enums ie NUI_SKELETON_POSITION_HIP_CENTER in place of joint
	ofPoint getSkeletonJoint(int,int); //Lerped Skeleton Point
	ofPoint getMappedJoint(int,int); //Raw, Scaled Joint
	ofPoint getRawJoint(int,int); //Raw unscaled joint

	

	int updateActivePlayer();
	bool isPlayerActive();


	ofxKinectNui* kinect;

	ofxKinectNuiPlayer kinectPlayer;
	ofxKinectNuiRecorder kinectRecorder;

	ofxBase3DVideo* kinectSource;

	ofTexture calibratedTexture;

	bool bRecord;
	bool bPlayback;
	bool bDrawVideo;
	bool bDrawDepthLabel;
	bool bDrawSkeleton;
	bool bDrawCalibratedTexture;
	bool bPlugged;
	bool bUnplugged;
		
	unsigned short nearClipping;
	unsigned short farClipping;
	int angle;

		
	int mRotationX, mRotationY;

	ofPoint skeletonLerpModel[ofxKinectNui::SKELETON_COUNT][ofxKinectNui::SKELETON_POSITION_COUNT];

	ofxKinectNuiDrawTexture*	videoDraw_;
	ofxKinectNuiDrawTexture*	depthDraw_;
	ofxKinectNuiDrawTexture*	labelDraw_;
	ofxKinectNuiDrawSkeleton*	skeletonDraw_;

};