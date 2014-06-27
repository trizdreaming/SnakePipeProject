#include "KinectController.h"

KinectController* KinectController::instance;

KinectController::KinectController(void)
{
}


KinectController::~KinectController(void)
{
}

void KinectController::InitKinect()
{
	openNIDevice.setup();
	openNIDevice.setSkeletonProfile(XN_SKEL_PROFILE_UPPER);
	openNIDevice.setResolution(640*2,480*2,30);
	openNIDevice.addDepthGenerator();
	openNIDevice.addImageGenerator();
	openNIDevice.setRegister(true);
	openNIDevice.setMirror(true);
	openNIDevice.setMaxNumUsers(100);
	openNIDevice.addUserGenerator();

	openNIDevice.start();
}

void KinectController::RenderSkeleton()
{
	int numUsers = openNIDevice.getNumTrackedUsers();

	for ( int i = 0 ; i < numUsers; ++i )
	{
		openNIDevice.drawSkeleton(0,0,640*2,480*2,i);
		ofxOpenNIUser &user = openNIDevice.getTrackedUser(i);

		if (!user.isSkeleton())
		{
			break;
		}

		ofxOpenNIJoint leftHand = user.getJoint(JOINT_LEFT_HAND);
		ofxOpenNIJoint leftShoulder = user.getJoint(JOINT_LEFT_SHOULDER);
		ofxOpenNIJoint rightHand = user.getJoint(JOINT_RIGHT_HAND);
		ofxOpenNIJoint rightShoulder = user.getJoint(JOINT_RIGHT_SHOULDER);

		m_leftHandPoint.x = (leftHand.getProjectivePosition().x)*2-15;
		m_leftHandPoint.y = (leftHand.getProjectivePosition().y)*2-15;
		m_rightHandPoint.x = (rightHand.getProjectivePosition().x)*2-15;
		m_rightHandPoint.y = (rightHand.getProjectivePosition().y)*2-15;
	}
}

void KinectController::Update()
{
	openNIDevice.update();
}

void KinectController::DrawImage()
{
	openNIDevice.drawImage(0,0,640*2,480*2);
}

void KinectController::Stop()
{
	openNIDevice.stop();
}
