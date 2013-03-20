#include "ofMain.h"
#include "ofxDelaunay.h"

class Delauney440 {

public:

	Delauney440() {};
	~Delauney440() {};
	void update(ofPolyline polyline, float alpha);


private:

	ofxDelaunay del;



};