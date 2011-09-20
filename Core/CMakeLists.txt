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

if( WIN32 )
set_target_properties( Core PROPERTIES COMPILE_FLAGS "/D_WIN32_WINNT=_WIN32_WINNT_WINXP" )
else( WIN32 )
set_target_properties( Core PROPERTIES COMPILE_FLAGS "-fPIC" )
endif( WIN32 )

target_link_libraries( Core
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES} )
					   
install( TARGETS Core ARCHIVE DESTINATION lib )
