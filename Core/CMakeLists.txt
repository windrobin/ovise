# Core

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIRS} )
					 
set( CoreHeaders
	Entity.h
	EntityPool.h
	SceneView.h )
	
set( CoreSources
	Entity.cpp
	EntityPool.cpp
	SceneView.cpp )
	
add_library( Core STATIC ${CoreHeaders} ${CoreSources} )

target_link_libraries( Core
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES} )
