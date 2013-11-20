#include "ofMain.h"

struct ScreenShot
{
	ofImage image;
	ofRectangle rect;
};


class ofApp : public ofBaseApp
{
	
public:
	
	void setup();
	void draw();
	void keyPressed(int key);
	
	void loadImages();
		
	vector<ScreenShot> screenshots;
	bool bPublishPDF;
	int num_images;
	int num_x;
	int num_y;
};


void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(255);
	
	
	// ---------------
	// trigger
	bPublishPDF = true;
	
	string path = "../../../../GoogleVideo/Downloads/";
	
	ofDirectory dir(path);
	//only show png files
	dir.listDir();
	
	//go through and print out all the paths
	for(int i = 0; i < dir.numFiles(); i++){
		ofLogNotice(dir.getPath(i));
	}
}


void ofApp::draw()
{
	
	ofExit();
}

void ofApp::keyPressed(int key)
{
	if (key == 'p')
	{
		bPublishPDF = true;
	}
}


//========================================================================
int main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());
}
