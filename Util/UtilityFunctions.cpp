#include "UtilityFunctions.h"
#include "SelectionBox.h"
#include "VertexData.h"

namespace OVISE
{

bool GetScreenspaceCoords( const Ogre::Vector3& Point, const Ogre::Camera* Camera, Ogre::Vector2& Result)
{
	// Is the camera facing that point? If not, return false
	Ogre::Plane CameraPlane = Ogre::Plane( 
		Ogre::Vector3( Camera->getDerivedOrientation().zAxis()), 
		Camera->getDerivedPosition());
	
	if( CameraPlane.getSide( Point ) != Ogre::Plane::NEGATIVE_SIDE)
		return false;
 
	// Transform the 3D point into screen space
	Ogre::Vector3 P = Camera->getProjectionMatrix() * (Camera->getViewMatrix() * Point );
 
	// Transform from coordinate space [-1, 1] to [0, 1] and update in-value
	Result.x = ( P.x / 2) + 0.5f;
	Result.y = 1 - ( ( P.y / 2) + 0.5f );
 
	return true;
}

Ogre::Entity* RaycastToPolygon( const Ogre::Real& x, const Ogre::Real& y,
	Ogre::RaySceneQuery* Query, Ogre::Camera* Camera )
{
	Ogre::Ray MouseRay = Camera->getCameraToViewportRay( x, y );
	Query->setRay( MouseRay );
	Query->setSortByDistance( true );

	Ogre::RaySceneQueryResult& QueryResult = Query->execute();

	if( QueryResult.size() == 0 )
	{
		return NULL;
	}

	// at this point we have raycast to a series of different objects bounding boxes. 
	// we need to test these different objects to see which is the first polygon hit. 
	// there are some minor optimizations (distance based) that mean we wont have to 
	// check all of the objects most of the time, but the worst case scenario is that 
	// we need to test every triangle of every object. 
	Ogre::Real ClosestDistance = -1.0f;
	Ogre::Entity* ClosestResult;

	for( size_t QRIndex = 0; QRIndex < QueryResult.size(); QRIndex++ ) 
	{ 
		// stop checking if we have found a raycast hit that is closer 
		// than all remaining entities 
		if( ( ClosestDistance >= 0.0f ) && 
			( ClosestDistance < QueryResult[QRIndex].distance ) )
			break; 
		
		// only check this result if its a hit against an entity 
		if( ( QueryResult[QRIndex].movable != NULL ) && 
			( QueryResult[QRIndex].movable->getMovableType().compare("Entity") == 0 ) &&
			QueryResult[QRIndex].movable->getName() != OVISE_SelectionBoxName ) 
		{ 
			// get the entity to check 
			Ogre::Entity* PEntity = static_cast<Ogre::Entity*>(QueryResult[QRIndex].movable);
			
			// mesh data to retrieve
			size_t VertexCount; 
			size_t IndexCount; 
			Ogre::Vector3* Vertices; 
			unsigned long* Indices;  
			
			// get the mesh information 
			GetMeshInformation( PEntity->getMesh(), 
				VertexCount, 
				Vertices, 
				IndexCount, 
				Indices, 
				PEntity->getParentSceneNode()->_getDerivedPosition(),
				PEntity->getParentSceneNode()->_getDerivedOrientation(), 
				PEntity->getParentSceneNode()->_getDerivedScale() );

			// test for hitting individual triangles on the mesh 
			bool NewClosestFound = false;
			if( IndexCount == 0 ) // no triangles, e.g. pointcloud
			{
				NewClosestFound = true;
				ClosestDistance = QueryResult[QRIndex].distance;
			}
			else
			{
				for( int i = 0; i < static_cast<int>(IndexCount); i += 3 ) 
				{ 
					// check for a hit against this triangle 
					std::pair<bool, Ogre::Real> Hit = 
						Ogre::Math::intersects( MouseRay, 
						Vertices[Indices[i]], 
						Vertices[Indices[i+1]], 
						Vertices[Indices[i+2]], 
						true, false);  
					// if it was a hit check if its the closest 
					if( Hit.first ) 
					{ 
						if( ( ClosestDistance < 0.0f ) || 
							( Hit.second < ClosestDistance ) ) 
						{ 
							// this is the closest so far, save it off 
							ClosestDistance = Hit.second; 
							NewClosestFound = true; 
						} 
					} 
				}
			}

			// free the verticies and indicies memory 
			delete[] Vertices;
			delete[] Indices;

			// if we found a new closest raycast for this object, update the 
			// closest_result before moving on to the next object. 
			if( NewClosestFound ) 
				ClosestResult = PEntity;
		}  
	}

	if( ClosestDistance < 0.0f ) 
	{
		// raycast failed 
		ClosestResult = NULL;
	}

	return ClosestResult;
}

} // namespace OVISE
