#include "ofMain.h"
#include "ofxSFPCPlotter.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	
	ofxSFPCPlotter plotter;
};


void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofxSFPCPlotter::Config conf;
	conf.plotterType = SFPC_PLT_TYPE_FIRSTCLASS;
	conf.penType = SFPC_PLT_PENTYPE_LED;
	plotter = ofxSFPCPlotter(conf);
	plotter.setup("test.svg");
	
	
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
	if (key == 'g') {
		plotter.stroke();
	}
}


//========================================================================
int main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());
}

