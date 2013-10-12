#include "ofMain.h"
#include "mofxBaseApp.h"


string cur_file;

int threshold;
int num_greater;

ofImage synth, img1;

class ofApp : public mofxBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void dragEvent(ofDragInfo dragInfo)
	{
		const string fileName = dragInfo.files[0];
		loadImage(fileName);
	}
	void loadImage(string filePath)
	{
		vector<string>hierarchy = ofSplitString(filePath, "/");
		
		if (hierarchy.size() > 1)
			cur_file = hierarchy.back();
		else
			cur_file = filePath;
		
		img1.loadImage(filePath);
		img1.resize(w, h);
		
		img1.setImageType(OF_IMAGE_GRAYSCALE);
	}
};

void ofApp::setup()
{
	ofSetFrameRate(3);
	ofSetVerticalSync(true);
	
	w = 300;
	h = 300;
	setWindowShape(w*2, h);
	
	synth.allocate(w, h, OF_IMAGE_GRAYSCALE);
	loadImage("1.jpg");
}

void ofApp::update()
{
	const int num_pixels = w * h;
	unsigned char *synth_pixels = synth.getPixels();
	unsigned char *img1_pixels = img1.getPixels();
	
	// update threshold by mouse position
	// threshold = ofMap(mouseX, 0, ofGetWidth(), 0, 255, true);
	
	// or automation...
	static const float speed = 2.0;
	static const float radius = 50.0;
	static const float start = 100;
	threshold = sinf(ofGetElapsedTimef() * speed) * radius + start;
	
	// reset counter
	num_greater = 0;
	
	// check pixel value
	for (int i=0; i<num_pixels; i++)
	{
		if (img1_pixels[i] > threshold)
		{
			num_greater++;
			synth_pixels[i] = 0;
		}
		else
		{
			synth_pixels[i] = 255;
		}
	}
	
	// update texture
	synth.update();
}

void ofApp::draw()
{
	// draw image
	ofSetColor(255);
	img1.draw(0, 0);
	synth.draw(w, 0);
	
	// draw text
	stringstream ss;
	ss << "drag and drop a image file to this window \n";
	ss << "file name: " + cur_file+ " \n";
	ss << "greater than: " + ofToString(threshold)+ " \n";
	ss << "total: " + ofToString(num_greater) + " / " + ofToString(w * h);
	
	ofSetColor(0);
	ofDrawBitmapString(ss.str(), ofPoint(20, 20));
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
