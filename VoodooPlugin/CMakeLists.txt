# VoodooPlugin

set( VoodooPlugin_VERSION_MAJOR 0 )
set( VoodooPlugin_VERSION_MINOR 1 )
set( VoodooPlugin_VERSION_PATCH 0 )

if( WIN32 )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/VoodooPlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/VoodooPlugin.rc )
endif( WIN32 )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( VoodooPluginHeaders
	 VoodooEntityView.h )

if( WIN32 )
set( VoodooPluginSources
	 VoodooEntityView.cpp
	 VoodooPlugin.rc )
else( WIN32 )
set( VoodooPluginSources
	 VoodooEntityView.cpp )
endif( WIN32 )
	 
add_library( VoodooPlugin SHARED ${VoodooPluginHeaders} ${VoodooPluginSources} )

if( WIN32 )
set_property( TARGET VoodooPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( VoodooPlugin PROPERTIES COMPILE_FLAGS "-fPIC"
                                               LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Visualization 
					       VERSION ${VoodooPlugin_VERSION_MAJOR}.${VoodooPlugin_VERSION_MINOR}.${VoodooPlugin_VERSION_PATCH} 
					       SOVERSION ${VoodooPlugin_VERSION_MAJOR}.${VoodooPlugin_VERSION_MINOR}.${VoodooPlugin_VERSION_PATCH} )
endif( UNIX )
			  
add_dependencies( VoodooPlugin
				  Core )
				  
target_link_libraries( VoodooPlugin
					   Core
					   Util
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )