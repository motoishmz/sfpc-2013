#pragma once

#include "ofMain.h"
#include "ofxSVGTiny.h"


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
	
	struct Point
	{
		float x = 0.0;
		float y = 0.0;
		bool bDraw = false;
	};
	
	ofxSFPCPlotter();
	ofxSFPCPlotter(Config conf);
	
	void reset();
	void start();
	void end();
	
	void setup(const string fileName);
	void update();
	void debugDraw();
	
	Point stepIn() const;
	
	inline void getEstimateTime(){ /* not impl */};
	inline bool isReady() const { return b_plotter_ready; };
	
protected:
	
	
	Config config;
	
	vector<ofPolyline> polylines;
	vector<ofPolyline> supLine;
	vector<ofPoint> points;
	vector<ofPoint> supPoints;
	
//	vector<Point> pathplan; // 
	
	ofVec2f pen_pos;
	ofRectangle drawable_area;
	bool b_plotter_ready;
	
	ofxSVGTiny svg;
	
	void setPlotterReady(const bool ready);
	void moveTo(float x, float y, bool bDraw);
	
	inline ofVec2f getPenPositionOnScreen() const
	{
		return pen_pos + drawable_area.getTopLeft();
	}
};