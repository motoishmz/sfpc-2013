#include "ofMain.h"
#include "mofxBaseApp.h"


class ofApp : public mofxBaseApp
{
	ofImage originalImage;
	ofImage shrinkedImage;
	ofRectangle white_area;
	
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
	
	void genShrinkedImage(int level, unsigned int thresh) // -20 ~ 20
	{
		static unsigned char * originalPixels = originalImage.getPixels();
		static unsigned char * newPixels = shrinkedImage.getPixels();
		
		int w = originalImage.width;
		int h = originalImage.height;
		
		for (int x=0; x<w; x++)
		{
			for (int y=0; y<h; y++)
			{
				int x_m_1 = x-level;
				int x_p_1 = x+level;
				if (x_m_1 < 0) x_m_1 = 0;
				if (x_p_1 > w-1) x_p_1 = w-1;
				
				int y_m_1 = y-level;
				int y_p_1 = y+level;
				if (y_m_1 < 0) y_m_1 = 0;
				if (y_p_1 > w-1) y_p_1 = h-1;
				
				int nw = y_m_1 * w + x_m_1;
				int n_ = y_m_1 * w + (x+0);
				int ne = y_m_1 * w + x_p_1;
				int e_ = (y+0) * w + x_p_1;
				int se = y_p_1 * w + x_p_1;
				int s_ = y_p_1 * w + (x+0);
				int sw = y_p_1 * w + x_m_1;
				int w_ = (y+0) * w + x_m_1;
				int me = (y+0) * w + (x+0);

				if (
					originalPixels[nw] > thresh ||
					originalPixels[n_] > thresh ||
					originalPixels[ne] > thresh ||
					originalPixels[e_] > thresh ||
					originalPixels[se] > thresh ||
					originalPixels[s_] > thresh ||
					originalPixels[sw] > thresh ||
					originalPixels[w_] > thresh
					)
				{
					newPixels[w_] = 255;
				}
				else
				{
					newPixels[w_] = 0;
				}
				
//				newPixels[me] =
//				
//				// sharp
//				-1 * originalPixels[nw] +
//				-1 * originalPixels[n_] +
//				-1 * originalPixels[ne] +
//				-1 * originalPixels[e_] +
//				-1 * originalPixels[se] +
//				-1 * originalPixels[s_] +
//				-1 * originalPixels[sw] +
//				-1 * originalPixels[w_] +
//				9 * originalPixels[me];

				// blur
//				(1 * originalPixels[nw] +
//				 1 * originalPixels[n_] +
//				 1 * originalPixels[ne] +
//				 1 * originalPixels[e_] +
//				 1 * originalPixels[se] +
//				 1 * originalPixels[s_] +
//				 1 * originalPixels[sw] +
//				 1 * originalPixels[w_] +
//				 1 * originalPixels[me]) / 9;
			}
		}
		
		shrinkedImage.update();
	}
};

int gain = 0;
int threshold = 0;

void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	string filename = "blob.png";
//	string filename = "test.png";
	
	originalImage.loadImage(filename);
	originalImage.setImageType(OF_IMAGE_GRAYSCALE);
	
	shrinkedImage.loadImage(filename);
	shrinkedImage.setImageType(OF_IMAGE_GRAYSCALE);
	
	w = originalImage.width*2;
	h = originalImage.height;
	
	setWindowShapa(w, h);
}

void ofApp::update()
{
//	threshold = ofMap(mouseX, 0, ofGetWidth(), 0, 255, true);
	threshold = 0;
	gain = ofMap(mouseY, 0, ofGetHeight(), -20, 20, true);
	
	genShrinkedImage(gain, threshold);
	white_area = getWhiteArea(shrinkedImage, threshold);
}

void ofApp::draw()
{
	// draw image
	ofSetColor(255);
	originalImage.draw(0, 0);
	shrinkedImage.draw(originalImage.width, 0);
//	
//	// draw blob
//	ofSetColor(255, 0, 0);
//	ofNoFill();
//	ofRect(white_area);
	
	// draw text
	stringstream ss;
	ss << "pixels greater than threshold: " + ofToString(threshold) + "\n";
	ss << "threshold:" + ofToString(threshold) + "\n";
	ss << "gain     :" + ofToString(gain) + "\n";
	
	ofSetColor(255, 0, 0);
	ofDrawBitmapString(ss.str(), ofPoint(20, 20));
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
