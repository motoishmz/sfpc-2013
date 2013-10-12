#include "ofMain.h"
#include "mofxBaseApp.h"


class ofApp : public mofxBaseApp
{
public:
	void setup();
	void update();
	void draw();
};

ofEasyCam cam;
ofLight light;
float sun_angle;
float solar_angle;

void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofSetWindowShape(w, h);
	
}

void ofApp::update()
{
	cam.setPosition(sinf(ofGetElapsedTimef() * 0.1) * 1000,
					200,
					cosf(ofGetElapsedTimef() * 0.1) * 1000);
	cam.lookAt(ofVec3f::zero());
}

void ofApp::draw()
{
	ofBackgroundGradient(ofColor(250), ofColor(150));
	
	static const float sun_size = 40; // sun radius
	static const float sec_per_day = 6.0; // speed
	static const float dist_from_earth = 400; // radius
	
	const float time = ofGetElapsedTimef() / sec_per_day;
	sun_angle = (time - (int)time) * 360;
	
	if (sun_angle < 90. || 270. < sun_angle)
	{
		static const float amount = 0.2;
		solar_angle = (sun_angle * amount) + (solar_angle * (1 - amount));
	}
	
	cam.begin();
	
	ofDrawAxis(1000);
	ofNoFill();
	
	ofPushMatrix();
	{
		// solar system
		static const float solar_height = 100;
		ofSetColor(0);
		ofRotateZ(solar_angle);
		ofTranslate(0, solar_height/2);
		ofDrawCone(ofVec3f::zero(), 30, solar_height);
		light.setPosition(ofVec3f::zero() + 20);
	}
	ofPopMatrix();
	ofPushMatrix();
	{
		// sun
		ofSetColor(255, 173, 0);
		ofRotateZ(sun_angle);
		ofTranslate(0, dist_from_earth);
		ofDrawSphere(sun_size);
	}
	ofPopMatrix();
	
	cam.end();
	
	
	stringstream ss;
	ss << "sun angle      : " + ofToString(sun_angle) + "\n";
	ss << "solar sys angle: " + ofToString(solar_angle) + "\n";
	ofSetColor(0);
	ofDrawBitmapString(ss.str(), ofPoint(20, 20));
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
