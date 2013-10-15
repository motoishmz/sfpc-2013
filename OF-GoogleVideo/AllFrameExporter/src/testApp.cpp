#include "ofMain.h"
#include "MovieSlicer.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void dragEvent(ofDragInfo dragInfo);
	
	MovieSlicer MS;
};


void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(255);
	
	MS.setup();
}

void ofApp::update()
{
	MS.update();
}

void ofApp::draw()
{
	ofSetHexColor(0xFFFFFF);
	MS.draw();
	
	ofSetHexColor(0xFF0000);
	ofDrawBitmapString(MS.getMessage(), ofPoint(20, 20));
	ofDrawBitmapString(MS.getErrorMessage(), ofPoint(20, 40));
}

void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_RETURN)
	{
		if (MS.canStartSlice())
			MS.slice();
	}
}

void ofApp::dragEvent(ofDragInfo dragInfo)
{
	const string filePath = dragInfo.files.at(0);
	MS.load(filePath);
}

//========================================================================
int main(){
	ofSetupOpenGL(500, 200, OF_WINDOW);
	ofRunApp(new ofApp());
}