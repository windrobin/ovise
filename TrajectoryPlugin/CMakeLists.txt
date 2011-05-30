# TrajectoryPlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( TrajectoryPluginHeaders
	 Trajectory.h
	 TrajectoryView.h )
	 
set( TrajectoryPluginSources
	 Trajectory.cpp
	 TrajectoryView.cpp )
	 
add_library( TrajectoryPlugin SHARED ${TrajectoryPluginHeaders} ${TrajectoryPluginSources} )

if( WIN32 )
set_property( TARGET TrajectoryPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( TrajectoryPlugin PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET TrajectoryPlugin PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( UNIX )
			  
add_dependencies( TrajectoryPlugin
				  Core )
				  
target_link_libraries( TrajectoryPlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )