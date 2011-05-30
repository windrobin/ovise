#ifndef TRAJECTORY_VIEW_H
#define TRAJECTORY_VIEW_H

#include "../Core/SceneView.h"
#include "Trajectory.h"

/** View for a trajectory consisting of a number of points in space.
 */
class TrajectoryView :
	public BasicOgreEntityView
{
public:
	TrajectoryView( Entity* Object, Ogre::SceneManager* Mgr );
	~TrajectoryView();

	void OnEntityAttributeChanged( Entity* Rhs, const std::string& Name, 
		const EntityVariantType* Attribute );

private:
	Ogre::SceneNode* mNode;
	
	boost::scoped_ptr<CTrajectory> mTrajectory;
};


#endif // TRAJECTORY_VIEW_H
