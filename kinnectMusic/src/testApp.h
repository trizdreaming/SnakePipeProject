#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "KinectController.h"
#include "Box.h"
#include "EnumSet.h"

class testApp : public ofBaseApp{

public:
    
	void setup(); 
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	void audioOut(float * input, int bufferSize, int nChannels);
	void PlayBGM();
	void StatusChange();
	void PipeStart();
	void PlayEffect();

private:
	STATUSSET m_Status;
	bool m_BgmCheck;
	bool m_PipeCheck;
	bool m_EffectCheck;
	bool m_ViewCheck;

	Box m_LeftHandBox;
	Box m_RightHandBox;

	Box m_Menu0;
	Box m_Menu1;
	Box m_Menu2;
	Box m_Menu3;

//	ofTexture m_Moon;


	//sound ฐüทร part
	ofSoundPlayer m_Sound;
	ofSoundPlayer m_EffectSound;

	ofSoundStream soundStream;

	float 	pan;
	int		sampleRate;
	bool 	bNoise;
	float 	volume;

	vector <float> lAudio;
	vector <float> rAudio;

	//------------------- for the simple sine wave synthesis
	float 	targetFrequency;
	float 	phase;
	float 	phaseAdder;
	float 	phaseAdderTarget;
};


#endif
