#include "ofMain.h"
#include "mofxBaseApp.h"


class ofApp : public mofxBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	ofRectangle getWhiteArea(ofImage &src, int threshold) const
	{
		ofRectangle area(ofGetWidth()/2, ofGetHeight()/2, 0, 0);
		
		const int num_pixels = src.width * src.height;
		unsigned char *pixels = src.getPixels();
		
		// check pixel value
		for (int x=0; x<src.width; x++)
		{
			for (int y=0; y<src.height; y++)
			{
				const unsigned char &pixel = pixels[y*src.width + x];
				
				if (pixel > threshold)
				{
					if (x <= area.x) area.x = x;
					if (y <= area.y) area.y = y;
					if (area.width <= x) area.width = x;
					if (area.height <= y) area.height = y;
				}
			}
		}
		
		if (area.width != 0) area.width -= area.x;
		if (area.height != 0) area.height -= area.y;
		
//		// logs
//		cout << "x:" << area.x << endl;
//		cout << "y:" << area.y << endl;
//		cout << "w:" << area.width << endl;
//		cout << "h:" << area.height << endl;
//		cout << "---" << endl;
		
		return area;
	}
};

int threshold = 0;

ofImage img;
ofRectangle white_area;

void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofSetWindowShape(w, h);
	
	img.loadImage("blob.png");
	img.setImageType(OF_IMAGE_GRAYSCALE);
	
}

void ofApp::update()
{
	threshold = ofMap(mouseX, 0, ofGetWidth(), 0, 255, true);
	white_area = getWhiteArea(img, threshold);
}

void ofApp::draw()
{
	// draw image
	ofSetColor(255);
	img.draw(0, 0);
	
	// draw blob
	ofSetColor(255, 0, 0);
	ofNoFill();
	ofRect(white_area);
	
	// draw text
	stringstream ss;
	ss << "pixels greater than threshold: " + ofToString(threshold) + "\n";
	ss << "min x:" + ofToString(white_area.x) + "\n";
	ss << "min y:" + ofToString(white_area.y) + "\n";
	ss << "max x:" + ofToString(white_area.width) + "\n";
	ss << "max y:" + ofToString(white_area.height) + "\n";
	
	ofSetColor(255, 0, 0);
	ofDrawBitmapString(ss.str(), ofPoint(20, 20));
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
