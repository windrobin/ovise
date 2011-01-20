# RobotPlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( RobotPluginHeaders
	 RobotEntityView.h )
	 
set( RobotPluginSources
	 RobotEntityView.cpp )
	 
add_library( RobotPlugin SHARED ${RobotPluginHeaders} ${RobotPluginSources} )

set_property( TARGET RobotPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins )

if( UNIX )
set_target_properties( RobotPlugin PROPERTIES COMPILE_FLAGS "-fPIC" )
endif( UNIX )
			  
add_dependencies( RobotPlugin
				  Core )
				  
target_link_libraries( RobotPlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )