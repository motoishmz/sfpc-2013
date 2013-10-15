#include "ofMain.h"
#include "converter.h"

#include "ofxGifEncoder.h"

class ofApp : public ofBaseApp
{
	
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key)
	{
		if (key == OF_KEY_UP)
		{
			gain++;
			img_synth = createGainedImage(img_binary, gain);
		}
		if (key == OF_KEY_DOWN)
		{
			gain--;
			img_synth = createGainedImage(img_binary, gain);
		}
		
		if (key == ' ')
		{
			frame.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			gifEncoder.addFrame(frame.getPixels(), ofGetWidth(), ofGetHeight(), frame.bpp, 0.5);
			cout << "added!" << endl;
		}
		
		if (key == 's')
		{
            cout <<"start saving\n" << endl;
            gifEncoder.save("test.gif");
		}
	}
	void onGifSaved(string &fileName)
	{
		cout << "saved!" << endl;
	}
	
	// ---
	
	vector<ofPoint> edge_points;
	ofImage img_original;
	ofImage img_binary;
	ofImage img_synth;
	int gain;
	
	float width, height;
	
	ofImage frame;
	ofxGifEncoder gifEncoder;
};


void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	// allocate original image
	img_original.loadImage("blob.png");
	img_original.setImageType(OF_IMAGE_GRAYSCALE);
	
	// generating binary image
	img_binary = createBinaryImage(img_original, 0);
	
	// search contour
	edge_points = getContour(img_binary);
	
	// dilate + erode
	gain = 0;
	img_synth = img_binary;
	
	// window resize
	width = img_original.width;
	height = img_original.height;
	ofSetWindowShape(width*2, height*2);
	
	// gif encoder
    gifEncoder.setup(width*2, width*2, .25, 256);
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &ofApp::onGifSaved);
}

void ofApp::update()
{
	ofSetWindowTitle( ofToString(ofGetFrameRate()) );
	
}

void ofApp::draw()
{
	// draw image
	ofSetColor(255);
	img_original.draw(0, 0);
	img_binary.draw(width, 0);
	img_binary.draw(0, height);
	img_synth.draw(width, height);
	
	ofSetColor(220, 14, 15);
	for (int i=0; i<edge_points.size(); i++)
		ofRect(edge_points[i] + ofPoint(0, height), 1, 1);
	
	
	/*!
		logs
	 */
	// labels
	ofSetColor(253, 180, 43);
	ofDrawBitmapString("Original", ofPoint(20, 20));
	ofDrawBitmapString("Binary", ofPoint(width+20, 20));
	ofDrawBitmapString("Binary+edge", ofPoint(20, height+20));
	
	// dilate + erode
	ofSetColor(253, 180, 255);
	ofDrawBitmapString("dilate + erode:", ofPoint(width+20, height+20));
	ofDrawBitmapString("press [UP] or [DOWN] to change the gain", ofPoint(width+20, height+40));
	ofDrawBitmapString("gain: " + ofToString(gain), ofPoint(width+20, height+60));
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
