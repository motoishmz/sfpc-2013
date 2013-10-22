#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void mouseDragged( int x, int y, int button )
	{
		ofPoint p;
		p.set(x, y);
		pts.push_back(p);
	}
	
	vector<ofPoint> pts;
	ofEasyCam cam;
};



void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofBackground(255);
}

void ofApp::update()
{
	
}

void ofApp::draw()
{
	const float f = ofGetElapsedTimef();
	
//	cam.begin();
	
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofRotateY(f * 30);
	
	ofDrawAxis(100);
	
	ofSetColor(255, 0, 0);
	ofNoFill();
	
	ofBeginShape();
	{
		for (int i=0; i<pts.size(); i++)
		{
			ofVertex(pts[i].x - ofGetWidth()/2,
					 pts[i].y - ofGetHeight()/2);
		}
	}
	ofEndShape();
	
//	cam.end();
	
}

void ofApp::keyPressed(int key)
{
	
}


//========================================================================
int main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());
}
