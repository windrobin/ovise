# SimplePlugin

set( SimplePlugin_VERSION_MAJOR 0 )
set( SimplePlugin_VERSION_MINOR 1 )
set( SimplePlugin_VERSION_PATCH 0 )

if( WIN32 )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/SimplePlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/SimplePlugin.rc )
endif( WIN32 )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( SimplePluginHeaders
	 SimpleEntityView.h )
	 
if( WIN32 )	 
set( SimplePluginSources
	 SimpleEntityView.cpp
	 SimplePlugin.rc )
else( WIN32 )
set( SimplePluginSources
	 SimpleEntityView.cpp )
endif( WIN32 )
	 
add_library( SimplePlugin SHARED ${SimplePluginHeaders} ${SimplePluginSources} )

if( WIN32 )
set_target_properties( SimplePlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( SimplePlugin PROPERTIES COMPILE_FLAGS "-fPIC"
                                               LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Visualization
					       VERSION ${SimplePlugin_VERSION_MAJOR}.${SimplePlugin_VERSION_MINOR}.${SimplePlugin_VERSION_PATCH}
					       SOVERSION ${SimplePlugin_VERSION_MAJOR}.${SimplePlugin_VERSION_MINOR}.${SimplePlugin_VERSION_PATCH} )
endif( UNIX )
			  
add_dependencies( SimplePlugin
				  Core )
				  
target_link_libraries( SimplePlugin
					   Core
					   Util
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )
					   
if( WIN32 )
install( TARGETS SimplePlugin RUNTIME CONFIGURATIONS Debug DESTINATION Plugins/Visualization/Debug )
install( TARGETS SimplePlugin RUNTIME CONFIGURATIONS Release DESTINATION Plugins/Visualization/Release )
elseif( UNIX )
install( TARGETS SimplePlugin LIBRARY DESTINATION Plugins/Visualization )
endif()