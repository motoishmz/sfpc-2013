#include "ofMain.h"
#include "ofxSVGTiny.h"
#include "ofxOsc.h"

static const int kSupply = 30;
static const int kSupplySub = 20;


class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void mousePressed( int x, int y, int button ){}
	void mouseMoved(int x, int y ){}
	
	class PlotterPath
	{
		
	public:
		
		PlotterPath(ofPoint p, bool draw)
		: pos(p)
		, bDraw(draw){};
		
		ofPoint pos;
		bool bDraw;
		
		ofPoint getClamped()
		{
			float x = ofMap(pos.x, 0, 600, 0, 1.0);
			float y = ofMap(pos.y, 0, 400, 0, 1.0);
			return ofPoint(x, y);
		}
	};
	
	inline ofVec2f getPenPositionOnScreen() const
	{
		return pen_pos + drawable_area.getTopLeft();
	}
	
	void stepIn()
	{
		curStep++;
		PlotterPath &p = plotterPaths[curStep];
		
		pen_pos_prev = pen_pos;
		pen_pos = p.pos;
		
		
		ofxOscMessage m;
		m.setAddress("/sfpcplotter");
		m.addFloatArg(p.getClamped().x);
		m.addFloatArg(p.getClamped().y);
		m.addIntArg(p.bDraw);
		sender.sendMessage(m);
	}
	
	vector<ofPolyline> polylines;
	vector<ofPoint> points;
	vector<ofPolyline> supLine;
	vector<ofPoint> supPoints;
	
	vector<PlotterPath> plotterPaths;
	
	int curStep;
	
	ofVec2f pen_pos_prev;
	ofVec2f pen_pos;
	ofRectangle drawable_area;
	
	ofxSVGTiny svg;
	ofxOscSender sender;
};


void ofApp::setup()
{
	
	sender.setup("192.168.0.242", 12345);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	// step
	curStep = 0;
	
	// area
	drawable_area.x = 0;
	drawable_area.y = 0;
	drawable_area.width = 600; // w:h = 15inch:10inch
	drawable_area.height = 400;
	
	// pen
	pen_pos.x = 0.;
	pen_pos.y = 0.;
	pen_pos_prev.x = 0.;
	pen_pos_prev.y = 0.;
	
	// svg
	svg.load("sfpc-pen.svg");
	
	// load polylines
	for (int i=0; i<svg.getNumPath(); i++)
	{
		ofPath path = svg.getPathAt(i);
		vector<ofPolyline> outline = path.getOutline();
		
		for (int oi=0; oi<outline.size(); oi++)
		{
			ofPolyline &pl = outline.at(oi);
			polylines.push_back(pl);
		}
	}
	
	
	// load points
	for (int i=0; i<polylines.size(); i++)
	{
		
		// adding polyline
		ofPolyline &pl = polylines.at(i);
		
		for (int suppl=0; suppl<kSupply; suppl++)
		{
			float pct = ofMap(suppl, 0, kSupply, 0, 1, true);
			ofPoint sup = pl.getPointAtPercent(pct);
			points.push_back(sup);
			
			// to be drawed
			plotterPaths.push_back( PlotterPath(sup, true) );
		}
		
		//
		points.push_back( pl.getVertices().back() );
		plotterPaths.push_back( PlotterPath(pl.getVertices().back(), true) );
		
		
		// move to next polyline
		if (i+1 != polylines.size())
		{
			ofPoint curLineEndPoint = points.back();
			ofPoint nextLineStartPoint = polylines.at(i+1).getVertices().front();
			
			ofPolyline pathToNextLine;
			pathToNextLine.addVertex(curLineEndPoint);
			pathToNextLine.addVertex(nextLineStartPoint);
			supLine.push_back(pathToNextLine);
			
			
			for (int suppl=0; suppl<kSupplySub; suppl++)
			{
				float pct = ofMap(suppl, 0, kSupplySub, 0, 1, true);
				ofPoint sup = pathToNextLine.getPointAtPercent(pct);
				supPoints.push_back(sup);
				
				
				// to be drawed
				plotterPaths.push_back( PlotterPath(sup, false) );
			}
		}
		
		cout << "----" << endl;
	}
}

void ofApp::update()
{
	
}

void ofApp::draw()
{
	// drawable area
	ofSetColor(50);
	ofNoFill();
	ofRect(drawable_area);
	
	
	// pen postion
	ofVec2f pen = getPenPositionOnScreen();
	
	ofSetColor(255, 100, 100);
	ofFill();
	ofCircle(pen, 5);
	
	ofLine(drawable_area.getLeft(),
		   pen.y,
		   drawable_area.getRight(),
		   pen.y);
	
	ofLine(pen.x,
		   drawable_area.getTop(),
		   pen.x,
		   drawable_area.getBottom());
	
	// polylines
	for (int i=0; i<polylines.size(); i++)
	{
		ofSetColor(0, 0, 255);
		polylines.at(i).draw();
	}
	
	// polylines
	for (int i=0; i<supLine.size(); i++)
	{
		ofSetColor(255, 0, 255);
		supLine.at(i).draw();
	}
	
	// points
	for (int i=0; i<plotterPaths.size(); i++)
	{
		PlotterPath &p = plotterPaths[i];
		
		if (p.bDraw) {
			ofSetColor(255, 0, 0);
		}
		else
		{
			ofSetColor(200);
		}
		ofCircle(p.pos, 3);
	}

//	// points
//	for (int i=0; i<points.size(); i++)
//	{
//		ofSetColor(0, 155, 255);
//		ofCircle(points.at(i), 3);
//	}
//
//	// points
//	for (int i=0; i<supPoints.size(); i++)
//	{
//		ofSetColor(255, 0, 255);
//		ofCircle(supPoints.at(i), 2);
//	}
	
	ofDrawBitmapStringHighlight(ofToString(pen_pos), pen.x + 20, pen.y - 20);

}

void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_RETURN) {
		stepIn();
	}
	if (key == 'c') {
		curStep = 0;
	}
	
}


//========================================================================
int main(){
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofApp());
}

