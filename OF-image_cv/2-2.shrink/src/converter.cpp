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

ofImage genContourImage(ofImage &src)
{
	float width = src.width;
	float height = src.height;
	
	ofImage contour;
	contour.allocate(width, height, OF_IMAGE_GRAYSCALE);
	
	unsigned char * srcPixels = src.getPixels();
	unsigned char * newPixels = contour.getPixels();
	
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			
            int x_m_1 = x - 1;
            int x_p_1 = x + 1;
            
            if (x_m_1 < 0) x_m_1 = 0;
            if (x_p_1 > width-1) x_p_1 = width-1;
            
            int y_m_1 = y - 1;
            int y_p_1 = y + 1;
            
            if (y_m_1 < 0) y_m_1 = 0;
            if (y_p_1 > height-1) y_p_1 = height-1;
            
            int ne = y_m_1 * width + x_p_1;
            int n_ = y_m_1 * width + (x+0);
            int nw = y_m_1 * width + x_m_1;
            int w_ = (y+0) * width + x_m_1;
            int sw = y_p_1 * width + x_m_1;
            int s_ = y_p_1 * width + (x+0);
            int se = y_p_1 * width + x_p_1;
            int e_ = (y+0) * width + x_p_1;
            int me = (y+0) * width + (x+0);   // <---- y * w + x
			
			float
				edge_n,
				edge_e,
				edge_s,
				edge_w;
			
            edge_n =
			-2 * srcPixels[ne] +
			-2 * srcPixels[n_] +
			-2 * srcPixels[nw] +
			 0 * srcPixels[w_] +
			 2 * srcPixels[sw] +
			 2 * srcPixels[s_] +
			 2 * srcPixels[se] +
			 0 * srcPixels[e_] +
			 0 * srcPixels[me];
			
			
//            edge_n =
//			-1 * srcPixels[ne] +
//			-1 * srcPixels[n_] +
//			-1 * srcPixels[nw] +
//			0 * srcPixels[w_] +
//			1 * srcPixels[sw] +
//			1 * srcPixels[s_] +
//			1 * srcPixels[se] +
//			0 * srcPixels[e_] +
//			0 * srcPixels[me];
//			
//            edge_e =
//			-1 * srcPixels[ne] +
//			 0 * srcPixels[n_] +
//			 1 * srcPixels[nw] +
//			 1 * srcPixels[w_] +
//			 1 * srcPixels[sw] +
//			 0 * srcPixels[s_] +
//			-1 * srcPixels[se] +
//			-1 * srcPixels[e_] +
//			 0 * srcPixels[me];
//			
//            edge_s =
//			 1 * srcPixels[ne] +
//			 1 * srcPixels[n_] +
//			 1 * srcPixels[nw] +
//			 0 * srcPixels[w_] +
//			-1 * srcPixels[sw] +
//			-1 * srcPixels[s_] +
//			-1 * srcPixels[se] +
//			 0 * srcPixels[e_] +
//			 0 * srcPixels[me];
//			
//            edge_w =
//			 1 * srcPixels[ne] +
//			 0 * srcPixels[n_] +
//			-1 * srcPixels[nw] +
//			-1 * srcPixels[w_] +
//			-1 * srcPixels[sw] +
//			 0 * srcPixels[s_] +
//			 1 * srcPixels[se] +
//			 1 * srcPixels[e_] +
//			 0 * srcPixels[me];
			
			newPixels[me] = edge_n;
		}
	}
	contour.update();
	
	return contour;
}






//	ofRectangle getWhiteArea(ofImage &src, int threshold) const
//	{
//		ofRectangle area(ofGetWidth()/2, ofGetHeight()/2, 0, 0);
//
//		const int num_pixels = src.width * src.height;
//		unsigned char *pixels = src.getPixels();
//
//		// check pixel value
//		for (int x=0; x<src.width; x++)
//		{
//			for (int y=0; y<src.height; y++)
//			{
//				const unsigned char &pixel = pixels[y*src.width + x];
//
//				if (pixel > threshold)
//				{
//					if (x <= area.x) area.x = x;
//					if (y <= area.y) area.y = y;
//					if (area.width <= x) area.width = x;
//					if (area.height <= y) area.height = y;
//				}
//			}
//		}
//
//		if (area.width != 0) area.width -= area.x;
//		if (area.height != 0) area.height -= area.y;
//
////		// logs
////		cout << "x:" << area.x << endl;
////		cout << "y:" << area.y << endl;
////		cout << "w:" << area.width << endl;
////		cout << "h:" << area.height << endl;
////		cout << "---" << endl;
//
//		return area;
//	}

//	void genShrinkedImage(int level, unsigned int thresh) // -20 ~ 20
//	{
//		static unsigned char * originalPixels = originalImage.getPixels();
//		static unsigned char * newPixels = shrinkedImage.getPixels();
//
//		int w = originalImage.width;
//		int h = originalImage.height;
//