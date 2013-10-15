#include "converter.h"


#define NUM_NEIGHBORHOODS 8
#define PIXEL_NOT_FOUND -1

ofImage createBinaryImage(ofImage &src, float threshold)
{
	int w = src.width;
	int h = src.height;
	
	ofImage binary;
	binary.allocate(w, h, OF_IMAGE_GRAYSCALE);
	
	unsigned char * srcPixels = src.getPixels();
	unsigned char * newPixels = binary.getPixels();
	
	for (int x=0; x<w; x++)
	{
		for (int y=0; y<h; y++)
		{
			unsigned char &sp = srcPixels[y*w + x];
			unsigned char &np = newPixels[y*w + x];
			
			if (sp > threshold)
				np = 255;
			else
				np = 0;
		}
	}
	
	binary.update();
	
	return binary;
}


vector<ofPoint> getContour(ofImage &src)
{
	vector<ofPoint> edge;
	
	ofPoint firstWhitePixel(0, 0);
	
	bool whitePixelFound = false;
	int width = src.width;
	int height = src.height;
	unsigned char * srcPixels = src.getPixels();
	
	
	// check the location of first white pixel
	for (int i=0; i < width*height; i++)
	{
		const unsigned char &pixel = srcPixels[i];
		
		if (pixel > 0)
		{
			firstWhitePixel.x = i%width;
			firstWhitePixel.y = i/height;
			
			whitePixelFound = true;
			break;
		}
	}
	
	// if there are no blobs
	if (whitePixelFound == false)
		return edge;
	
	// push first pixel
	edge.push_back(firstWhitePixel);
	
	/*!
	 !!!:search_direction
	 
	 7 0 1
	 6 x 2
	 5 4 3
	 */
	int search_direction = 0;
	
	ofPoint nextPoint = findNextContour(firstWhitePixel, src, search_direction);
	
	while (firstWhitePixel != nextPoint)
	{
		edge.push_back(nextPoint);
		
		search_direction = (search_direction+5) % 8;
		nextPoint = findNextContour(nextPoint, src, search_direction);
		
		if (nextPoint.x < 0) // default value of findNeighborhood() is ofPoint(-1, -1)
			break;
	}
	
	return edge;
}


ofPoint findNextContour(ofPoint me, ofImage &src, int &search_direction)
{
	ofPoint neighborhood(-1, -1);
	
	bool whitePixelFound = false;
	unsigned char * srcPixels = src.getPixels();
	
	// set neighberhods pixels' index to *indeces
	int indeces[NUM_NEIGHBORHOODS];
	findNeighborhoods(indeces, src, me);
	
	// checking pixels clockwise whether black or white
	int next_pixel = -1;
	
	for (int i=0; i<NUM_NEIGHBORHOODS; i++)
	{
		const int &index = indeces[search_direction];
		search_direction = (search_direction+1) % NUM_NEIGHBORHOODS;
		
		if (index == PIXEL_NOT_FOUND)
			continue;
		
		if (srcPixels[index] > 0)
		{
			next_pixel = index;
			break;
		}
	}
	
	// if neighborhood is not found, then kill
	assert(next_pixel != -1);
	
	neighborhood.x = next_pixel % src.width;
	neighborhood.y = next_pixel / src.height;
	
	return neighborhood;
}


void findNeighborhoods(int *neighborhoods, ofImage &src, ofPoint &me)
{
	//	assert(&neighborhoods / sizeof(int) == NUM_NEIGHBORHOODS);
	
	// start point (me)
	int x = me.x;
	int y = me.y;
	
	// image size
	int w = src.width;
	int h = src.height;
	
	enum contour_search_direction { n_ = 0, ne, e_, se, s_, sw, w_, nw };
	
	neighborhoods[n_] = (y-1) * w + (x+0); // n_
	neighborhoods[ne] = (y-1) * w + (x+1); // ne
	neighborhoods[e_] = (y+0) * w + (x+1); // e_
	neighborhoods[se] = (y+1) * w + (x+1); // se
	neighborhoods[s_] = (y+1) * w + (x+0); // s_
	neighborhoods[sw] = (y+1) * w + (x-1); // sw
	neighborhoods[w_] = (y+0) * w + (x-1); // w_
	neighborhoods[nw] = (y-1) * w + (x-1); // nw
	
	// left end
	if (me.x == 0)
	{
		neighborhoods[w_] = PIXEL_NOT_FOUND;
		neighborhoods[sw] = PIXEL_NOT_FOUND;
		neighborhoods[nw] = PIXEL_NOT_FOUND;
	}
	
	// right end
	if (me.x >= src.width)
	{
		neighborhoods[e_] = PIXEL_NOT_FOUND;
		neighborhoods[ne] = PIXEL_NOT_FOUND;
		neighborhoods[se] = PIXEL_NOT_FOUND;
	}
	
	// top end
	if (me.y == 0)
	{
		neighborhoods[n_] = PIXEL_NOT_FOUND;
		neighborhoods[ne] = PIXEL_NOT_FOUND;
		neighborhoods[nw] = PIXEL_NOT_FOUND;
	}
	
	// bottom end
	if (me.y >= src.height)
	{
		neighborhoods[s_] = PIXEL_NOT_FOUND;
		neighborhoods[se] = PIXEL_NOT_FOUND;
		neighborhoods[sw] = PIXEL_NOT_FOUND;
	}
	
	return neighborhoods;
}


ofImage createGainedImage(ofImage &src, int gain)
{
	if (gain == 0) return src;
	
	ofImage gainedImage = src;
	
	for (int i=0; i<abs(gain); i++)
	{
		vector<ofPoint> edges = getContour(gainedImage);
		
		for (int p=0; p<edges.size(); p++)
		{
			ofPoint &point = edges.at(p);
			
			if (gain > 0)
				dilate(gainedImage, point);
			else
				erode(gainedImage, point);
		}
	}
	
	return gainedImage;
}


void dilate(ofImage &src, ofPoint point)
{
	int neighborhoods[NUM_NEIGHBORHOODS];
	findNeighborhoods(neighborhoods, src, point);
	
	unsigned char * srcPixels = src.getPixels();
	
	for (int i=0; i<NUM_NEIGHBORHOODS; i++)
	{
		const int &index = neighborhoods[i];
		srcPixels[index] = 255;
	}
	
	src.update();
}


void erode(ofImage &src, ofPoint point)
{
	int neighborhoods[NUM_NEIGHBORHOODS];
	findNeighborhoods(neighborhoods, src, point);
	
	unsigned char * srcPixels = src.getPixels();
	
	for (int i=0; i<NUM_NEIGHBORHOODS; i++)
	{
		const int &index = neighborhoods[i];
		srcPixels[index] = 0;
	}
	
	src.update();
}

























