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
ofImage genContourImage(ofImage &src);


ofRectangle getWhiteArea(float threshold);

