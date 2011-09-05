#include <OGRE/OgreManualObject.h>
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>

#include <boost/noncopyable.hpp>

const std::string OVISE_SelectionBoxName = "__SelectionBox";

class CSelectionBox : private boost::noncopyable
{
public:
	CSelectionBox( Ogre::SceneManager* SceneMgr );
	virtual ~CSelectionBox();

	void Show( Ogre::Entity* Target );
	void Hide();

private:
	Ogre::Vector3 mSize;
	Ogre::SceneNode* mParent;

	Ogre::ManualObject* mVisual;

	void Resize( const Ogre::Vector3& Size );
};
