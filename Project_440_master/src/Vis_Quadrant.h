#pragma once
#include "Visualizer.h"
class Vis_Quadrant :
	public Visualizer
{
public:
	Vis_Quadrant(void);
	~Vis_Quadrant(void);

	void setup();
	void update();
	void draw();
	void getBands();
	void start();
	void stop();
};

