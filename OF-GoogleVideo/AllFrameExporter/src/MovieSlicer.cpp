#include "MovieSlicer.h"

void MovieSlicer::setup()
{
	ofThread::ofThread();
	MP.setPixelFormat(OF_PIXELS_RGBA);
	MP.setLoopState(OF_LOOP_NONE);
	
	setState(MPWaiting);
	setErrorMessage(MPErrorNon);
}

void MovieSlicer::update()
{
	if (state != MPConverting)
		return;
	
	frame.setFromPixels(MP.getPixelsRef());
	frame.saveImage("frame-" + ofToString(MP.getCurrentFrame()) + ".png");
	
	MP.nextFrame();
	current_frame = MP.getCurrentFrame();
	
	message = ofToString(current_frame) + "/" + ofToString(total_frame);
	
	if( MP.getCurrentFrame() == total_frame )
		setState(MPFinish);
}
void MovieSlicer::draw()
{
	if (frame.isAllocated())
		frame.draw(0, 0);
}

bool MovieSlicer::load(const string filePath)
{
	bool succeeded = MP.loadMovie(filePath);
	
	if (succeeded)
	{
		setState(MPStandBy);
		setErrorMessage(MPErrorNon);
	}
	else
	{
		setState(MPWaiting);
		setErrorMessage(MPErrorLoad);
	}
	
	return succeeded;
}
void MovieSlicer::slice()
{
	setState(MPConverting);
}

void MovieSlicer::setState(const MPState newState)
{
	state = newState;

	switch (state)
	{
		case MPWaiting:

			message = "wating... drag & drop your movie file to the window.";
			break;

		case MPStandBy:

			ofSetWindowShape(MP.getWidth(), MP.getHeight());

			MP.firstFrame();
			
			frame.setFromPixels(MP.getPixelsRef());
			total_frame = MP.getTotalNumFrames();

			message = ofToString(total_frame) + " Press [Enter] to start slicing.";
			break;

		case MPConverting:

			message = "slicing...";

			break;

		case MPFinish:
			message = "Done.";
			break;
			
		default:
			break;
	}

}
void MovieSlicer::setErrorMessage(const MPErrorState errorState)
{
	error_state = errorState;
	
	switch (error_state)
	{
		case MPErrorNon:
			error_message = "";
			break;
			
		case MPErrorLoad:
			error_message = "couldn't load the dropped file.";
			break;
		default:
			break;
	}
}