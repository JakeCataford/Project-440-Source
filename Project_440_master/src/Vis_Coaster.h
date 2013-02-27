#pragma once
#include "Visualizer.h"
class Vis_Coaster :
	public Visualizer
{
public:
	Vis_Coaster(void);
	~Vis_Coaster(void);

	void setup();
	void update();
	void draw();
	void getBands();
	void start();
	void stop();
};

