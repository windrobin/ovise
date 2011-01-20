# PointcloudPlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( PointcloudPluginHeaders
	 PointcloudEntityView.h
	 Pointcloud.h )
	 
set( PointcloudPluginSources
	 PointcloudEntityView.cpp
	 Pointcloud.cpp )
	 
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