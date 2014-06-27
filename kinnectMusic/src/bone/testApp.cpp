#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);
	
	openNIDevice.setup();
	openNIDevice.setSkeletonProfile(XN_SKEL_PROFILE_UPPER);
    openNIDevice.setResolution(640*2,480*2,30);
	openNIDevice.addDepthGenerator();
	openNIDevice.addImageGenerator();
	openNIDevice.setRegister(true);
	openNIDevice.setMirror(true);
	openNIDevice.setMaxNumUsers(2);
	openNIDevice.addUserGenerator();

	openNIDevice.start();
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
}

//--------------------------------------------------------------
void testApp::draw(){

	
	openNIDevice.drawImage(0,0,640*2,480*2);
	
	ofPushMatrix();
	int numUsers = openNIDevice.getNumTrackedUsers();

	for ( int i = 0 ; i < numUsers; ++i )
	{
		openNIDevice.drawSkeleton(openNIDevice.getWidth()/2-320,openNIDevice.getHeight()/2-250,openNIDevice.getWidth()*2.0,openNIDevice.getHeight()*2.0,i);
		ofxOpenNIUser &user = openNIDevice.getTrackedUser(i);

		if (!user.isSkeleton())
		{
			break;
		}

		ofxOpenNIJoint leftHand = user.getJoint(JOINT_LEFT_HAND);
		ofxOpenNIJoint leftShoulder = user.getJoint(JOINT_LEFT_SHOULDER);
		ofxOpenNIJoint rightHand = user.getJoint(JOINT_RIGHT_HAND);
		ofxOpenNIJoint rightShoulder = user.getJoint(JOINT_RIGHT_SHOULDER);

		ofPoint leftHandPoint = leftHand.getProjectivePosition();
		ofPoint leftShoulderPoint = leftShoulder.getProjectivePosition();
		ofPoint rightHandPoint = rightHand.getProjectivePosition();
		ofPoint rightShoulderPoint = rightShoulder.getProjectivePosition();
	}

	ofPopMatrix();
	
    
    // draw some info regarding frame counts etc
// 	ofSetColor(0, 255, 0);
// 	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
//     
// 	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
}

//--------------------------------------------------------------
//이건 로그
// void testApp::handEvent(ofxOpenNIHandEvent & event){
//     // show hand event messages in the console
//     ofLogNotice() << getHandStatusAsString(event.handStatus) << "for hand" << event.id << "from device" << event.deviceID;
// }

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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