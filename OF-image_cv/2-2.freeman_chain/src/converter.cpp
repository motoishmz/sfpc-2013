#include "converter.h"


ofImage genBinaryImage(ofImage &src, float threshold)
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
	
	assert(whitePixelFound == true);
	
	edge.push_back(firstWhitePixel);
	
	cout << "firstWhitePixel:" << firstWhitePixel << endl;
	
	/*!
		!!!:search_direction
		
		7 0 1
		6 x 2
		5 4 3
	 */
	int search_direction = 0;
	
	ofPoint nextPoint = findNeighborhood(firstWhitePixel, src, search_direction);
	
	while (firstWhitePixel != nextPoint)
	{
		edge.push_back(nextPoint);
		
		cout << "nextPoint:" << nextPoint << endl;
		
		nextPoint = findNeighborhood(nextPoint, src, search_direction);
		
		if (nextPoint.x < 0) // default value of findNeighborhood() is ofPoint(-1, -1)
			break;
	}
	
	return edge;
}


ofPoint findNeighborhood(ofPoint base, ofImage &src, int &search_direction)
{
	ofPoint neighborhood(-1, -1);
	
	bool whitePixelFound = false;
	unsigned char * srcPixels = src.getPixels();
	int w = src.width;
	int h = src.height;
	
	// start point (me)
	int x = base.x;
	int y = base.y;

	// neighborhood pixels position
	// !!!:
	int numIndeces = 8;
	int indeces[] =
	{
		(y-1) * w + (x+0), // n_
		(y-1) * w + (x+1), // ne
		(y+0) * w + (x+1), // e_
		(y+1) * w + (x+1), // se
		(y+1) * w + (x+0), // s_
		(y+1) * w + (x-1), // sw
		(y+0) * w + (x-1), // w_
		(y-1) * w + (x-1)  // nw
	};
	
	// checking pixels clockwise whether black or white
	int next_pixel = -1;
	for (int i=0; i<numIndeces; i++)
	{
		const int &index = indeces[search_direction];
		search_direction = (search_direction+1) % numIndeces;
		
		if (srcPixels[index] > 0)
		{
			next_pixel = index;
			
			cout << i << endl;
			break;
		}
	}
	
	// if neighborhood is not found, then kill
//	assert(next_pixel != -1);
	
	// convert (int)next_pixel >> ofPoint
	neighborhood.x = next_pixel % w;
	neighborhood.y = next_pixel / w;
	
	return neighborhood;
}
