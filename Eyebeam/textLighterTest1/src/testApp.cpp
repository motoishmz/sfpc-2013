#include "ofMain.h"
#include "ofxSFPCPlotter.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void mousePressed( int x, int y, int button )
	{
	}
	void mouseMoved(int x, int y )
	{
	}
	
	ofPoint drag_start;
	
	ofxSFPCPlotter plotter;
	ofxSFPCPlotter::Point current;
	ofxSFPCPlotter::Point next;
};


void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	plotter.setup("sfpc-pen.svg");
}

void ofApp::update()
{
	
}

void ofApp::draw()
{
	plotter.debugDraw();
}

void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_RETURN) {
		plotter.stepIn();
	}
	
	if (key == 's') {
		plotter.start();
	}
	
	if (key == 'e') {
		plotter.end();
	}
}


//========================================================================
int main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());
}

