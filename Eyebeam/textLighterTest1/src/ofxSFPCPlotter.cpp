#include "ofxSFPCPlotter.h"


ofxSFPCPlotter::ofxSFPCPlotter()
{
	Config conf;
	config = conf;
	
}
ofxSFPCPlotter::ofxSFPCPlotter(Config conf)
{
	config = conf;
}

void ofxSFPCPlotter::reset()
{
	paths.clear();
	b_plotter_ready = false;
}

void ofxSFPCPlotter::setup(const string fileName)
{
	// load something
	// set to paths
	// set ready
}

void ofxSFPCPlotter::update()
{
	
}

void ofxSFPCPlotter::debugDraw()
{
	ofPushStyle();
	{
		ofCircle(pen_pos, 5);
	}
	ofPopStyle();
}

ofxSFPCPlotter::Path ofxSFPCPlotter::stroke() const
{

}
