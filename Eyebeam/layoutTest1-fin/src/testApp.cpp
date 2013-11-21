#include "ofMain.h"

//#define USE_TEST
//#define NUM_IMAGES 15
bool use_frame = true;

struct ScreenShot
{
	ofImage image;
	ofColor color;
};


ofColor basecolor = ofColor(255, 200, 150);

class ofApp : public ofBaseApp
{
	
public:
	void setup();
	void draw();
	void keyPressed(int key);
	
	void loadImages();
		
	vector<ScreenShot> screen_shots;
	bool bPublishPDF;
	
	ofRectangle frame_window;
	ofRectangle frame_image;
	
	int num_images;
	int num_row = 7;
	int num_col;
	float margin_right = 60;
	float padding;
	
	const float scale = 0.8;
	const float line_width = 10;
};



void ofApp::setup()
{
	
	
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(255);
	
	
	// ---------------
	// trigger
	bPublishPDF = false;

	
	// ---------------
	// screenshots
	string path = "~/Documents/Codes/openFrameworks/0080/sfpc-2013/Eyebeam/Resized";
	ofDirectory dir(path);
	dir.listDir();
	num_images = dir.numFiles();
	
	
	// ---------------
	// window size / image size
	frame_window.height = 3080; // 42inch in 300dpi
	frame_image.height = frame_window.height / (num_row + 1.);
	frame_image.width = frame_image.height / 3 * 4; // 4 : 3
	padding = frame_image.height / 2.;
	num_col = ceil(num_images / (float)num_row);
	frame_window.width = (num_col * frame_image.width) + (padding * 2) + num_col * margin_right;
	
	
	// ---------------
	// scaling
	padding *= scale;
	frame_image.width *= scale;
	frame_image.height *= scale;
	frame_window.width *= scale;
	frame_window.height *= scale;
	
	ofSetWindowShape(frame_window.width, frame_window.height);
	cout << "window size: " << frame_window << endl;
	cout << "image size: " << frame_image << endl;
	cout << "padding" << padding << endl;
	
	
	// ---------------
	// loading all images
	
	const float hue_start = 255 / 360. * 100;
	const float hue_end = 255 / 360. * 360;
	
	for(int i = 0; i < num_images; i++)
	{
		
		const string path = dir.getPath(i);
		cout << i << ": " << path << endl;
		
		int id = ofToInt( ofSplitString(ofSplitString(path, "/").back(), "-").at(0) );

		
		
		ScreenShot ss;
		float hue = ofMap(id, 0, 9, hue_start, hue_end);
		ss.color = basecolor;
		ss.color.setHue(hue);
		if (id == 0 )
			ss.color = ofColor(226);
		
		ss.image.loadImage(path);
		if (use_frame)
			ss.image.resize(frame_image.width - line_width*2, frame_image.height - line_width*2);
		else
			ss.image.resize(frame_image.width, frame_image.height);
		ss.image.update();
		screen_shots.push_back(ss);
	}
}


void ofApp::draw()
{
	if (bPublishPDF)
	{
		ofBeginSaveScreenAsPDF("test.pdf", false);
	}

	ofSetColor(255);
	for (int x=0; x<num_col; x++)
	{
		for (int y=0; y<num_row; y++)
		{
			const int cur_index = x*num_row + y;
			if (cur_index >= num_images) break;
			
			ofPoint pos(x*frame_image.width + padding + margin_right * x, y*frame_image.height + padding);
			ScreenShot &ss = screen_shots.at(cur_index);
			
			ofPushMatrix();
			{
				ofTranslate(pos);
				
				
				// ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
				// draw frame
				if (use_frame)
				{
					ofSetColor(ss.color);
					ofSetLineWidth(6);
					ofFill();
					ofLine(-30, 0, 0, 0);
					ofLine(-27, 0, -27, 30);
				}
				
				
				// ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
				// draw image
				ofSetColor(255);
				ofPushMatrix();
				{
					if (use_frame)
						ofTranslate(line_width, line_width);
					ss.image.draw(0, 0);
				}
				ofPopMatrix();
				
			}
			ofPopMatrix();
			
// ---------------------
//			testImage.draw(ofPoint(x*100, y*100), 100, 1000);
		}
	}
	
	if (bPublishPDF)
	{
		ofEndSaveScreenAsPDF();
		bPublishPDF = false;
	}
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
