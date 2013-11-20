#include "testApp.h"

bool oneShot;

//--------------------------------------------------------------
void testApp::setup(){
	
	oneShot = false;
	
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	if( oneShot ){
		ofBeginSaveScreenAsPDF("screenshot-"+ofGetTimestampString()+".pdf", false);
	}
	
	
	for (int x=0; x<10; x++)
	{
		for (int y=0; y<10; y++)
		{
			ofSetColor(0);
			ofNoFill();
			ofCircle(x*100, y*100, 100);
		}
	}
	
	
	if( oneShot ){
		ofEndSaveScreenAsPDF();
		oneShot = false;
	}	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if( key == 's' ){
		oneShot = true;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

