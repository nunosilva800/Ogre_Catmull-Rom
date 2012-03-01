/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "stdafx.h"
#include "TutorialApplication.h"

using namespace Ogre;
using namespace OgreBites;

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // create your scene here :)

	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	// Create a light
	Ogre::Light * l = mSceneMgr->createLight("MainLight");
	l->setPosition(20, 80, 50);

	// entities and scenes
	//Ogre::Entity * ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

	//Ogre::SceneNode * headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");

	// attach the entities to the scene nodes
	//headNode->attachObject(ogreHead);



	// pre-load the mesh so that we can tweak it with a manual animation
	mHeadMesh = MeshManager::getSingleton().load("facial.mesh", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	// create a manual animation, create a pose track for it, and create a keyframe in that track
	mManualKeyFrame = mHeadMesh->createAnimation("Manual", 0)->createVertexTrack(4, VAT_POSE)->createVertexPoseKeyFrame(0);
	mManualKeyFrame2 = mHeadMesh->createAnimation("Manual2", 0)->createVertexTrack(4, VAT_POSE)->createVertexPoseKeyFrame(0);

	// create pose references for the first 15 poses
	for (unsigned int i = 0; i < 15; i++) mManualKeyFrame->addPoseReference(i, 0);
	for (unsigned int i = 0; i < 15; i++) mManualKeyFrame2->addPoseReference(i, 0);

	// create a head entity from the mesh and attach it to a node with a vertical offset to center it
	Entity* head = mSceneMgr->createEntity("Head", "facial.mesh");
	mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(-25, -30, 0))->attachObject(head);
	mManualAnimState = head->getAnimationState("Manual");
	mManualAnimState->setEnabled(true);

	Entity* head2 = mSceneMgr->createEntity("Head2", "facial.mesh");
	mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(25, -30, 0))->attachObject(head2);
	mManualAnimState2 = head2->getAnimationState("Manual2");
	mManualAnimState2->setEnabled(true);

		
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
