# RobotPlugin

set( RobotPlugin_VERSION_MAJOR 0 )
set( RobotPlugin_VERSION_MINOR 1 )
set( RobotPlugin_VERSION_PATCH 0 )

if( WIN32 )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/RobotPlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/RobotPlugin.rc )
endif( WIN32 )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( RobotPluginHeaders
	 RobotEntityView.h )
	 
if( WIN32 )
set( RobotPluginSources
	 RobotEntityView.cpp
	 RobotPlugin.rc )
else( WIN32 )
set( RobotPluginSources
	 RobotEntityView.cpp )
endif( WIN32 )
	 
add_library( RobotPlugin SHARED ${RobotPluginHeaders} ${RobotPluginSources} )

if( WIN32 )
set_property( TARGET RobotPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( RobotPlugin PROPERTIES COMPILE_FLAGS "-fPIC"
                                              LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Visualization
					      VERSION ${RobotPlugin_VERSION_MAJOR}.${RobotPlugin_VERSION_MINOR}.${RobotPlugin_VERSION_PATCH} 
					      SOVERSION ${RobotPlugin_VERSION_MAJOR}.${RobotPlugin_VERSION_MINOR}.${RobotPlugin_VERSION_PATCH} )
endif( UNIX )
			  
add_dependencies( RobotPlugin
				  Core )
				  
target_link_libraries( RobotPlugin
					   Core
					   Util
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )
					   
if( WIN32 )
install( TARGETS RobotPlugin RUNTIME CONFIGURATIONS Debug DESTINATION Plugins/Visualization/Debug )
install( TARGETS RobotPlugin RUNTIME CONFIGURATIONS Release DESTINATION Plugins/Visualization/Release )
elseif( UNIX )
install( TARGETS RobotPlugin LIBRARY DESTINATION Plugins/Visualization )
endif()