#pragma once

#include "ofMain.h"

enum PlotterType {
	SFPC_PLT_TYPE_FIRSTCLASS = 0
};

enum PlotterPenType {
	SFPC_PLT_PENTYPE_LED = 0
};



class ofxSFPCPlotter
{
	
public:
	
	struct Config
	{
		PlotterType plotterType = SFPC_PLT_TYPE_FIRSTCLASS;
		PlotterPenType penType = SFPC_PLT_PENTYPE_LED;
	};
	
	struct Path
	{
		float x = 0.0;
		float y = 0.0;
		bool bDraw = false;
	};
	
	ofxSFPCPlotter();
	ofxSFPCPlotter(Config conf);
	
	void reset();
	
	void setup(const string fileName);
	void update();
	void debugDraw();
	
	Path stroke() const;
	
	inline void getEstimateTime(){ /* not impl */};
	inline void getNumStroke() const { return paths.size(); };
	inline bool isReady() const { return b_plotter_ready; };
	
protected:
	
	
	Config config;
	vector<Path> paths;
	
	ofVec2f pen_pos;
	ofRectangle drawable_area;
	
	bool b_plotter_ready;
	
	
	void moveTo(float x, float y, bool bDraw);
};