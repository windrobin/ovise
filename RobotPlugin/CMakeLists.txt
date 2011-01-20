# RobotPlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( RobotPluginHeaders
	 RobotEntityView.h )
	 
set( RobotPluginSources
	 RobotEntityView.cpp )
	 
add_library( RobotPlugin SHARED ${RobotPluginHeaders} ${RobotPluginSources} )

if( WIN32 )
set_property( TARGET RobotPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( RobotPlugin PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET RobotPlugin PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( UNIX )
			  
add_dependencies( RobotPlugin
				  Core )
				  
target_link_libraries( RobotPlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )