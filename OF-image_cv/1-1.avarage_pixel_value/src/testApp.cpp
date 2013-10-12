#include "ofMain.h"

float w = 500;
float h = 500;
float avarage_pixel_value = 0;
string cur_file;

ofImage synth, img1;

class ofApp : public ofBaseApp
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
		
		synthImage();
	}
	void synthImage()
	{
		const int num_pixels = w * h;
		unsigned char *synth_pixels = synth.getPixels();
		unsigned char *img1_pixels = img1.getPixels();
		
		// amount
		for (int i=0; i<num_pixels; i++)
			avarage_pixel_value += img1_pixels[i];
		
		// calc avarage
		avarage_pixel_value /= num_pixels;
		
		// set to synth image
		for (int i=0; i<num_pixels; i++)
			synth_pixels[i] = avarage_pixel_value;
		
		// update texture
		synth.update();
	}
};

void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofSetWindowShape(w*2, h);
	synth.allocate(w, h, OF_IMAGE_GRAYSCALE);
	
	loadImage("1.jpg");
}

void ofApp::update()
{
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
	ss << "avarage: " + ofToString(avarage_pixel_value);
	
	ofSetColor(0);
	ofDrawBitmapString(ss.str(), ofPoint(20, 20));
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
