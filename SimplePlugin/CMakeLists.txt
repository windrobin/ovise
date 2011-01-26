# SimplePlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( SimplePluginHeaders
	 SimpleEntityView.h )
	 
set( SimplePluginSources
	 SimpleEntityView.cpp )
	 
add_library( SimplePlugin SHARED ${SimplePluginHeaders} ${SimplePluginSources} )

if( WIN32 )
set_property( TARGET SimplePlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( SimplePlugin PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET SimplePlugin PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( UNIX )
			  
add_dependencies( SimplePlugin
				  Core )
				  
target_link_libraries( SimplePlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )