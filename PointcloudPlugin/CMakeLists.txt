# PointcloudPlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( PointcloudPluginHeaders
	 PointcloudEntityView.h
	 Pointcloud.h )
	 
set( PointcloudPluginSources
	 PointcloudEntityView.cpp
	 Pointcloud.cpp )
	 
add_library( PointcloudPlugin SHARED ${PointcloudPluginHeaders} ${PointcloudPluginSources} )

set_property( TARGET PointcloudPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins )
			  
add_dependencies( PointcloudPlugin
				  Core )
				  
target_link_libraries( PointcloudPlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )