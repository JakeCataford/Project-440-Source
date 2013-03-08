#include "Wireframe.h"

void Wireframe::init(Kinect440 & ref, Audio440 & aud) {
	kinect = &ref;
	audio = &aud;

}

void Wireframe::clearPointers() {
	
}

void Wireframe::draw() {
	
	vector <ofPoint> pts = kinect->getContour();
	
	printf("Checking if empty...");
	if(!pts.empty() && pts.size() < 10000){

	printf("Looping for vals, got %i...", pts.size());
	for(int i = 0; i <pts.size(); i ++) {
		polyline.push_back(new p2t::Point(pts.at(i).x,pts.at(i).y));
	}
	printf("Creating CDT...");
	p2t::CDT * delauney = new p2t::CDT(polyline);


	printf("Triangulating...");
	delauney->Triangulate();

	printf("Getting trangles...");
	vector <p2t::Triangle *> tris = delauney->GetTriangles();

	for(int i = 0; i < tris.size(); i++){
		ofPushStyle();
		ofSetColor(255);
		ofNoFill();
		ofTriangle(ofPoint(ofMap(tris.at(i)->GetPoint(0)->x,5,90,10,ofGetWidth()-10,true),
						   ofMap(tris.at(i)->GetPoint(0)->y,5,70,10,ofGetHeight()-10,true)),ofPoint(
						   ofMap(tris.at(i)->GetPoint(1)->x,5,90,10,ofGetWidth()-10,true),  
						   ofMap(tris.at(i)->GetPoint(1)->y,5,70,10,ofGetHeight()-10,true)),ofPoint(
						   ofMap(tris.at(i)->GetPoint(2)->x,5,90,10,ofGetWidth()-10,true), 
						   ofMap(tris.at(i)->GetPoint(2)->y,5,70,10,ofGetHeight()-10,true)));
		ofPopStyle();

	}

	printf("clearing...");
	while(!polyline.empty()) {
		delete polyline.back(), polyline.pop_back();
	}

	polyline.clear();


	 delete delauney;
	}

}
