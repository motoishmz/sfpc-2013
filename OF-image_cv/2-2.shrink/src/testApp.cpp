#include "ofMain.h"
#include "converter.h"


/*
	画像のcenterを求めるのをやめた。このファイルでは...
	1. edgeを求める
	2. edgeのerode/dilate functionを作る
	3. gainの数だけloopする
 */


class ofApp : public ofBaseApp
{
	
public:
	void setup();
	void update();
	void draw();
};

ofImage img_original;
ofImage img_binary;
ofImage img_contour;
ofPoint center;

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
	
	// contour
	img_contour = genContourImage(img_binary);
	
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
	img_contour.draw(0, height);
	
	ofSetColor(255, 0, 0);
	ofCircle(center, 10);
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
