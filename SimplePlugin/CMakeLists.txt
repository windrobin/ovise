# SimplePlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( SimplePluginHeaders
	 SimpleEntityView.h )
	 
set( SimplePluginSources
	 SimpleEntityView.cpp )
	 
add_library( SimplePlugin SHARED ${SimplePluginHeaders} ${SimplePluginSources} )

set_property( TARGET SimplePlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins )
			  
add_dependencies( SimplePlugin
				  Core )
				  
target_link_libraries( SimplePlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )