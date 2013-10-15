#pragma once

#include "ofImage.h"

/*!
	@returns ofImage: binary image
	@paramms ofImage src: original image
	@paramms float threshold: pixel less than threshold will be discard
 */
ofImage createBinaryImage(ofImage &src, float threshold);

/*!
	@returns vector<ofPoint>: edge points
	@paramms ofImage src: original image
 */
vector<ofPoint> getContour(ofImage &src);
ofPoint findNextContour(ofPoint me, ofImage &src, int &search_direction);

void findNeighborhoods(int *neighborhoods, ofImage &src, ofPoint &me);


/*!
	 @returns ofImage: dilated or eroded image
	 @params ofImage &src: binary image
	 @params int gain: gain power
 */
ofImage createGainedImage(ofImage &src, int gain);
void dilate(ofImage &src, ofPoint point);
void erode(ofImage &src, ofPoint point);
