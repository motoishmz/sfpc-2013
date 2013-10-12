#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	
	ofImage synth, img1, img2;
};

float w = 501;
float h = 501;
int draw_target = 0;

void ofApp::setup()
{
	ofSetFrameRate(10);
	ofSetVerticalSync(true);
	
	ofSetWindowShape(w, h);
	
	img1.loadImage("1.jpg");
	img2.loadImage("2.jpg");
	
	img1.resize(w, h);
	img2.resize(w, h);
	
	img1.setImageType(OF_IMAGE_GRAYSCALE);
	img2.setImageType(OF_IMAGE_GRAYSCALE);
	synth.allocate(w, h, OF_IMAGE_GRAYSCALE);
}

void ofApp::update()
{
	int step = 1;
	
	unsigned char *synth_pixels = synth.getPixels();
	unsigned char *img1_pixels = img1.getPixels();
	unsigned char *img2_pixels = img2.getPixels();
	
	for (int x=0; x<w; x+=step)
	{
		for (int y=0; y<h; y+=step)
		{
			const int index = y*w + x;
			synth_pixels[index] = index%2 ? img1_pixels[index] : img2_pixels[index];
		}
	}
	
	synth.update();
}

void ofApp::draw()
{
	if (draw_target == 0)
		synth.draw(0,0);
	else if (draw_target == 1)
		img1.draw(0, 0);
	else
		img2.draw(0, 0);
}

void ofApp::keyPressed(int key)
{
	if (key == ' ')
	{
		draw_target++;
		
		const int max = 2;
		if (draw_target > max)
			draw_target = 0;
	}
}


//========================================================================
int main(){
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
}
