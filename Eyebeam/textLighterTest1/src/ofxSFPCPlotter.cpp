#include "ofxSFPCPlotter.h"



ofxSFPCPlotter::ofxSFPCPlotter()
{
	Config conf;
	config = conf;
	reset();
}
ofxSFPCPlotter::ofxSFPCPlotter(Config conf)
{
	config = conf;
	reset();
}

void ofxSFPCPlotter::reset()
{
//	vector<Path> paths;
//	ofRectangle drawable_area;
//	ofVec2f pen_pos;
//	bool b_plotter_ready;

	// path
//	pathplan.clear();
	
	// area
	drawable_area.x = 0;
	drawable_area.y = 0;
	drawable_area.width = 600; // w:h = 15inch:10inch
	drawable_area.height = 400;
	
	// pen
	pen_pos.x = 0;
	pen_pos.y = 0;
	
	// ready?
	setPlotterReady(false);
}
void ofxSFPCPlotter::start()
{
	// cam start
}
void ofxSFPCPlotter::end()
{
	// cam end
}


// --------------------------------------


void ofxSFPCPlotter::setup(const string fileName)
{
	// load something
	svg.load(fileName);
	
	
	cout << svg.getWidth() << endl;
	cout << svg.getHeight() << endl;
	
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
	int num_suppliment = 11;
	for (int i=0; i<polylines.size(); i++)
	{
		
		// adding polyline
		ofPolyline &pl = polylines.at(i);
		
		for (int suppl=0; suppl<num_suppliment; suppl++)
		{
			float pct = ofMap(suppl, 0, num_suppliment, 0, 1, true);
			ofPoint sup = pl.getPointAtPercent(pct);
			points.push_back(sup);
		}
		points.push_back(pl.getVertices().back());
		
		
		// move to next polyline
		if (i+1 != polylines.size())
		{
			ofPoint curLineEndPoint = points.back();
			ofPoint nextLineStartPoint = polylines.at(i+1).getVertices().front();
			
			ofPolyline pathToNextLine;
			pathToNextLine.addVertex(curLineEndPoint);
			pathToNextLine.addVertex(nextLineStartPoint);
			supLine.push_back(pathToNextLine);
			
			int num_suppliment_to_next = 7;

			for (int suppl=0; suppl<num_suppliment_to_next; suppl++)
			{
				float pct = ofMap(suppl, 0, num_suppliment_to_next, 0, 1, true);
				ofPoint sup = pathToNextLine.getPointAtPercent(pct);
				supPoints.push_back(sup);
			}
		}
		
		cout << "----" << endl;
	}

	
	// fit paths to canvas
	float svgWidth = svg.getWidth();
	float svgHeight = svg.getHeight();
	float wRatio = 1.0;
	float hRatio = 1.0;
	
	if (svg.getWidth() > drawable_area.width)
	{
		wRatio /= (float)svg.getWidth() / drawable_area.width;
		svgWidth *= wRatio;
		svgHeight *= wRatio;
	}
	if (svgHeight > drawable_area.height)
	{
		hRatio /= (float)svgHeight / drawable_area.height;
		svgWidth *= hRatio;
		svgHeight *= hRatio;
	}
	
	// polylines
	for (int i=0; i<polylines.size(); i++)
	{
		polylines.at(i).draw();
	}
	
	// polylines
	for (int i=0; i<supLine.size(); i++)
	{
		ofSetColor(255, 0, 255);
		supLine.at(i).draw();
	}
	
	// points
	for (int i=0; i<points.size(); i++)
	{
		ofSetColor(0, 155, 255);
		ofCircle(points.at(i), 3);
	}
	
	// points
	for (int i=0; i<supPoints.size(); i++)
	{
		ofSetColor(255, 0, 255);
		ofCircle(supPoints.at(i), 2);
	}
	
	
	
	// set ready
	setPlotterReady(true);
}

void ofxSFPCPlotter::update()
{
	
}

void ofxSFPCPlotter::debugDraw()
{
	ofPushStyle();
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
			   pen.y,
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
		for (int i=0; i<points.size(); i++)
		{
			ofSetColor(0, 155, 255);
			ofCircle(points.at(i), 3);
		}
		
		// points
		for (int i=0; i<supPoints.size(); i++)
		{
			ofSetColor(255, 0, 255);
			ofCircle(supPoints.at(i), 2);
		}
		
		ofDrawBitmapStringHighlight(ofToString(pen_pos), pen.x + 20, pen.y - 20);
	}
	ofPopStyle();
}

ofxSFPCPlotter::Point ofxSFPCPlotter::stepIn() const
{
	
}


#pragma mark -
#pragma mark
void ofxSFPCPlotter::setPlotterReady(const bool ready)
{
	b_plotter_ready = ready;
}

