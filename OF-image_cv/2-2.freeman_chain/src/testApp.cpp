#include "ofMain.h"
#include "converter.h"

class ofApp : public ofBaseApp
{
	
public:
	void setup();
	void update();
	void draw();
};

ofImage img_original;
ofImage img_binary;
ofPoint p;

vector<ofPoint> edge_points;

float width, height;
string filename = "blob.png";

void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	// allocate original image
	img_original.loadImage(filename);
	img_original.setImageType(OF_IMAGE_GRAYSCALE);
	
	// generating binary image
	img_binary = genBinaryImage(img_original, 0);
	
	// search contour
	edge_points = getContour(img_binary);
	
	// window resize
	width = img_original.width;
	height = img_original.height;
	ofSetWindowShape(width*2, height*2);
}

void ofApp::update()
{

}

void ofApp::draw()
{
	// draw image
	ofSetColor(255);
	img_original.draw(0, 0);
	img_binary.draw(width, 0);
	
	ofSetColor(255, 0, 0);
	
	for (int i=0; i<edge_points.size(); i++)
	{
		ofCircle(edge_points[i], 1);
	}
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
