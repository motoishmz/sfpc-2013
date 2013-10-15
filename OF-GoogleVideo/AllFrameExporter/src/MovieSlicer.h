//
//  MovieSlicer.h
//  videoPlayerExample
//
//  Created by motoishmz on 9/3/13.
//
//

#include "ofMain.h"

enum MPState
{
	MPWaiting = 0,
	MPStandBy,
	MPConverting,
	MPFinish
};

enum MPErrorState
{
	MPErrorNon = 0,
	MPErrorLoad
};

class MovieSlicer
{
	int total_frame;
	int current_frame;
	
	ofVideoPlayer MP;
	ofImage frame;
	
	string file_path;
	
	MPState state;
	MPErrorState error_state;
	string message;
	string error_message;
	
	void setState(const MPState newState);
	void setErrorMessage(const MPErrorState errorState);
	
public:
	
	void setup();
	void update();
	void draw();
	
	bool load(const string filePath);
	void slice();
	
	inline bool canStartSlice(){ return state == MPStandBy; }
	
	inline string getMessage(){ return message; }
	inline string getErrorMessage(){ return error_message; }
};