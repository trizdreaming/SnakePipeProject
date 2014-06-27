#include "testApp.h"
#include "KinectController.h"

#define  DEFAULT_POSITION ofPoint(100,0);

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);
	KinectController::getInstance()->InitKinect();

//	ofBackground(0,0,0);
	

	m_Sound.loadSound("SongoftheMountain.mp3");
	m_EffectSound.loadSound("effect.wav");

	m_RightHandBox.setWidth(30);
	m_RightHandBox.setHeight(30);
	m_RightHandBox.SetColor(255,0,0);
	
	m_LeftHandBox.setWidth(30);
	m_LeftHandBox.setHeight(30);
	m_RightHandBox.SetColor(255,0,0);

	ofSetLineWidth(2);
	m_Menu0.setWidth(130);
	m_Menu0.setHeight(35);
	m_Menu0.setPosition(50,150);
	m_Menu0.SetColor(255,0,0);
	m_Menu1.SetisVisible();

	ofSetLineWidth(2);
	m_Menu1.setWidth(130);
	m_Menu1.setHeight(35);
	m_Menu1.setPosition(50,200);
	m_Menu1.SetColor(255,0,0);
	m_Menu1.SetisVisible();

	ofSetLineWidth(2);
	m_Menu2.setWidth(130);
	m_Menu2.setHeight(35);
	m_Menu2.setPosition(50,250);
	m_Menu2.SetColor(255,0,0);
	m_Menu2.SetisVisible();

	ofSetLineWidth(2);
	m_Menu3.setWidth(130);
	m_Menu3.setHeight(35);
	m_Menu3.setPosition(50,350);
	m_Menu3.SetColor(255,0,0);
	m_Menu3.SetisVisible();

	m_Status =  STATUS_CAMERA;
	m_BgmCheck = false;
	m_PipeCheck = false;
	m_EffectCheck = false;
	m_ViewCheck = false;

// 	ofImage moon;
// 	moon.loadImage("moon.png");
// 	m_Moon.allocate(256,256, GL_RGB, true);
// 	m_Moon.loadData(moon.getPixels(),256,256,GL_RGB);

	// 2 output channels,
	// 0 input channels
	// 22050 samples per second
	// 512 samples per buffer
	// 4 num buffers (latency)

	int bufferSize		= 512;
	sampleRate 			= 44100;
	phase 				= 0;
	phaseAdder 			= 0.0f;
	phaseAdderTarget 	= 0.0f;
	volume				= 0.00f;

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);

	//soundStream.listDevices();

	//if you want to set the device id to be different than the default
	//soundStream.setDeviceID(1); 	//note some devices are input only and some are output only 

	soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);

	ofSetFrameRate(60);

	soundStream.stop();

}

bool BoxCollision(Box box1, Box box2)
{
	if(box1.getMinX() <= box2.getMaxX() && box1.getMaxX() >= box2.getMinX() &&
		box1.getMinY() <= box2.getMaxY() && box1.getMaxY() >= box2.getMinY())
	{
		return true;
	}
	return false;
}

void testApp::PlayBGM()
{
	m_Sound.play();
}
void testApp::StatusChange()
{

	m_Status = STATUS_VIEW;
	
}
void testApp::PipeStart()
{
	soundStream.start();
}
void testApp::PlayEffect()
{
	m_EffectSound.play();
}

//--------------------------------------------------------------
void testApp::update(){

	KinectController::getInstance()->Update();
	m_BgmCheck = BoxCollision(m_LeftHandBox, m_Menu0);

	if (m_BgmCheck)
	{
		PlayBGM();
		m_BgmCheck = false;
	}

	m_PipeCheck = BoxCollision(m_LeftHandBox, m_Menu1);

	if (m_PipeCheck)
	{
		PipeStart();
		m_PipeCheck = false;
	}

	m_EffectCheck = BoxCollision(m_LeftHandBox,m_Menu2);
	if (m_EffectCheck)
	{
		PlayEffect();
		m_EffectCheck = false;
	}

	m_ViewCheck = BoxCollision(m_LeftHandBox, m_Menu3);
	if (m_ViewCheck)
	{
		StatusChange();
		m_ViewCheck = false;
	}

	int width = ofGetWidth();
	pan = (float)(KinectController::getInstance()->getRightHandPoint().x) / (float)width;
	float height = (float)(ofGetHeight()-250);

	//volume = (float)KinectController::getInstance()->getLeftHandPoint().x / (float)width;
	if (KinectController::getInstance()->getLeftHandPoint().x>100 &&KinectController::getInstance()->getLeftHandPoint().x<450)
	{
		volume = 1.f;
	}
	else
	{
		volume = 0.f;
	}

	float heightPct = (float)((height-KinectController::getInstance()->getRightHandPoint().y) / height);
	if (heightPct<0)
	{
		heightPct = 0;
	}

	targetFrequency = 1500.0f * heightPct;
	phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;

}

//--------------------------------------------------------------
void testApp::draw(){



	if (m_Status == STATUS_CAMERA)
	{
		ofPushMatrix();

		KinectController::getInstance()->DrawImage();
		

		ofPopMatrix();
	}
	else if (m_Status == STATUS_VIEW)
	{
		ofSetBackgroundColor(255,35,35);
		
		//audio output
		ofSetColor(225);
		ofNoFill();

		// draw the left channel:
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(132, 150, 0);

		ofSetColor(225);
		ofDrawBitmapString("Left Channel", 104, 18);

		ofSetLineWidth(1);	
		ofRect(100, 0, 900, 200);

		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);

		ofBeginShape();
		for (unsigned int i = 0; i < lAudio.size(); i++){
			float x =  ofMap(i, 0, lAudio.size(), 0, 900, true)+100;
			ofVertex(x, 100 -lAudio[i]*180.0f);
		}
		ofEndShape(false);

		ofPopMatrix();
		ofPopStyle();

		// draw the right channel:
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(32, 350, 0);

		ofSetColor(225);
		ofDrawBitmapString("Right Channel", 4, 18);

		ofSetLineWidth(1);	
		ofRect(0, 0, 900, 200);

		ofSetColor(245, 58, 135);
		ofSetLineWidth(3);

		ofBeginShape();
		for (unsigned int i = 0; i < rAudio.size(); i++){
			float x =  ofMap(i, 0, rAudio.size(), 0, 900, true);
			ofVertex(x, 100 -rAudio[i]*180.0f);
		}
		ofEndShape(false);

		ofPopMatrix();
		ofPopStyle();


		ofSetColor(225);
		string reportString = "volume: ("+ofToString(volume, 2)+") modify with -/+ keys\npan: ("+ofToString(pan, 2)+") modify with mouse x\nsynthesis: ";

		reportString += "sine wave (" + ofToString(targetFrequency, 2) + "hz) modify with mouse y";

		ofDrawBitmapString(reportString, 32, 579);
	}

	ofPushMatrix();
	KinectController::getInstance()->RenderSkeleton();

	m_LeftHandBox.setPosition(KinectController::getInstance()->getLeftHandPoint());
	m_RightHandBox.setPosition(KinectController::getInstance()->getRightHandPoint());

	m_RightHandBox.Draw();
	m_LeftHandBox.Draw();

	m_Menu0.Draw();
	ofSetColor(255,0,0);
	ofDrawBitmapString("PLAY BGM ON", 65, 170);

	m_Menu1.Draw();
	ofSetColor(255,0,0);
	ofDrawBitmapString("Start Pipe", 65, 220);

	m_Menu2.Draw();
	ofSetColor(255,0,0);
	ofDrawBitmapString("effect Sound", 65, 270);

	m_Menu3.Draw();
	ofSetColor(255,0,0);
	ofDrawBitmapString("change View", 55, 370);

	ofSetColor(255,255,255);
	ofPopMatrix();
}


//--------------------------------------------------------------
void testApp::exit(){
	KinectController::getInstance()->Stop();
	KinectController::getInstance()->Release();
}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
//	pan = 0.5f;
	float leftScale = 1 - pan;
	float rightScale = pan;

	// sin (n) seems to have trouble when n is very large, so we
	// keep phase in the range of 0-TWO_PI like this:
	while (phase > TWO_PI){
		phase -= TWO_PI;
	}

	
	//phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
	phaseAdder = 0.4f * phaseAdder + 0.6f * phaseAdderTarget;
	for (int i = 0; i < bufferSize; i++){
		phase += phaseAdder;
		float sample = sin(phase);
		lAudio[i] = output[i*nChannels    ] = sample * volume * leftScale;
		rAudio[i] = output[i*nChannels + 1] = sample * volume * rightScale;
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == '-' || key == '_' ){
		volume -= 0.05;
		volume = MAX(volume, 0);
	} else if (key == '+' || key == '=' ){
		volume += 0.05;
		volume = MIN(volume, 1);
	}

	if( key == 's' ){
		soundStream.start();
	}

	if( key == 'e' ){
		soundStream.stop();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

	/*
	int width = ofGetWidth();
	pan = (float)x / (float)width;
	float height = (float)(ofGetHeight()-250);

	float heightPct = ((height-y) / height);
	if (heightPct<0)
	{
		heightPct = 0;
	}
	
	targetFrequency = 1500.0f * heightPct;
	phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;	*/// 	int width = ofGetWidth();
// 	pan = (float)(KinectController::getInstance()->getRightHandPoint().x) / (float)width;
// 	float height = ofGetHeight();
// 	float heightPct = (float)((height-KinectController::getInstance()->getRightHandPoint().y) / height);
// 	targetFrequency = 4000.f * heightPct;
// 	phaseAdderTarget = (targetFrequency/(float)sampleRate)*TWO_PI;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
// 	int width = ofGetWidth();
// 	pan = (float)x / (float)width;
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


