#include "Delauney.h"

void Delauney440::update(ofPolyline poly, float alpha) {

	if(poly.size() > 9) {
		
		ofPushStyle();
		del.reset();
		del.addPoints(poly.getVertices());
		del.triangulate();
		del.triangleMesh.clearColors();
		for(int i = 0; i < del.triangleMesh.getVertices().size(); i++) {
			if(i % 4 == 0) {
				del.triangleMesh.addColor(ofColor(255,255,255,alpha));
			}else if(i % 4 == 1){
				del.triangleMesh.addColor(ofColor(0,255,255,alpha));
			}else if(i % 4 == 2){
				del.triangleMesh.addColor(ofColor(0,0,0,alpha));
			}else if(i % 4 == 3){
				del.triangleMesh.addColor(ofColor(0,0,100,alpha));
			}
		}

		del.triangleMesh.drawWireframe();
		ofPopStyle();
		
	}


}