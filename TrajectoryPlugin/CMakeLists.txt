# TrajectoryPlugin

set( TrajectoryPlugin_VERSION_MAJOR 0 )
set( TrajectoryPlugin_VERSION_MINOR 1 )
set( TrajectoryPlugin_VERSION_PATCH 0 )

if( WIN32 )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/TrajectoryPlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/TrajectoryPlugin.rc )
endif( WIN32 )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( TrajectoryPluginHeaders
	 Trajectory.h
	 TrajectoryView.h )
	 
if( WIN32 )
set( TrajectoryPluginSources
	 Trajectory.cpp
	 TrajectoryView.cpp
	 TrajectoryPlugin.rc )
else( WIN32 )
set( TrajectoryPluginSources
	 Trajectory.cpp
	 TrajectoryView.cpp )
endif( WIN32 )
	 
add_library( TrajectoryPlugin SHARED ${TrajectoryPluginHeaders} ${TrajectoryPluginSources} )

if( WIN32 )
set_property( TARGET TrajectoryPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( TrajectoryPlugin PROPERTIES COMPILE_FLAGS "-fPIC"
                                                   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Visualization 
						   VERSION ${TrajectoryPlugin_VERSION_MAJOR}.${TrajectoryPlugin_VERSION_MINOR}.${TrajectoryPlugin_VERSION_PATCH} 
						   SOVERSION ${TrajectoryPlugin_VERSION_MAJOR}.${TrajectoryPlugin_VERSION_MINOR}.${TrajectoryPlugin_VERSION_PATCH} )
endif( UNIX )
			  
add_dependencies( TrajectoryPlugin
				  Core )
				  
target_link_libraries( TrajectoryPlugin
					   Core
					   Util
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )