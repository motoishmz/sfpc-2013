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
	
	ofPolyline poly;
	vector<ofPoint> pts;
	
	ofVec3f rotate;
};



void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofBackground(255);
}

void ofApp::update()
{
	if (ofGetKeyPressed('1')) rotate.x = 1;
	if (ofGetKeyPressed('2')) rotate.x = 0;
	if (ofGetKeyPressed('3')) rotate.y = 1;
	if (ofGetKeyPressed('4')) rotate.y = 0;
	if (ofGetKeyPressed('5')) rotate.z = 1;
	if (ofGetKeyPressed('6')) rotate.z = 0;
	
//	for (int i=0; i<.size(); i++)
//	{
//		
//	}
	
}

void ofApp::draw()
{
	const float f = ofGetElapsedTimef();
	
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofRotate(f*10, rotate.x, rotate.y, rotate.z);
	
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
}

void ofApp::keyPressed(int key)
{
	
}


//========================================================================
int main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());
}
