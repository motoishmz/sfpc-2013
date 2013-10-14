#pragma once

#include "ofImage.h"


/*!
	@paramms ofImage src: original image
	@paramms float threshold: pixel less than threshold will be discard
 */
ofImage genBinaryImage(ofImage &src, float threshold);

/*!
 @paramms ofImage src: original image
 */
vector<ofPoint> getContour(ofImage &src);
ofPoint findNeighborhood(ofPoint base, ofImage &src, int &search_direction);

ofRectangle getWhiteArea(float threshold);
