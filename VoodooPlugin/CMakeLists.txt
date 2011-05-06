# VoodooPlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( VoodooPluginHeaders
	 VoodooEntityView.h )
	 
set( VoodooPluginSources
	 VoodooEntityView.cpp )
	 
add_library( VoodooPlugin SHARED ${VoodooPluginHeaders} ${VoodooPluginSources} )

if( WIN32 )
set_property( TARGET VoodooPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( VoodooPlugin PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET VoodooPlugin PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( UNIX )
			  
add_dependencies( VoodooPlugin
				  Core )
				  
target_link_libraries( VoodooPlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )