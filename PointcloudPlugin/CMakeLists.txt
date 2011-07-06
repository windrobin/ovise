# PointcloudPlugin

set( PointcloudPlugin_VERSION_MAJOR 0 )
set( PointcloudPlugin_VERSION_MINOR 1 )
set( PointcloudPlugin_VERSION_PATCH 0 )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/PointcloudPlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/PointcloudPlugin.rc )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( PointcloudPluginHeaders
	 PointcloudEntityView.h
	 Pointcloud.h )
	 
if( WIN32 )
set( PointcloudPluginSources
	 PointcloudEntityView.cpp
	 Pointcloud.cpp
	 PointcloudPlugin.rc )
else( WIN32 )
set( PointcloudPluginSources
	 PointcloudEntityView.cpp
	 Pointcloud.cpp )
endif( WIN32 )
	 
add_library( PointcloudPlugin SHARED ${PointcloudPluginHeaders} ${PointcloudPluginSources} )

if( WIN32 )
set_property( TARGET PointcloudPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( PointcloudPlugin PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET PointcloudPlugin PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( UNIX )

			  
add_dependencies( PointcloudPlugin
				  Core )
				  
target_link_libraries( PointcloudPlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${wxWidgets_LIBRARIES}
					   ${Boost_LIBRARIES} )