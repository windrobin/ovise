# SkeletalPlugin

set( SkeletalPlugin_VERSION_MAJOR 0 )
set( SkeletalPlugin_VERSION_MINOR 1 )
set( SkeletalPlugin_VERSION_PATCH 0 )

if( WIN32 )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/SkeletalPlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/SkeletalPlugin.rc )
endif( WIN32 )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( SkeletalPluginHeaders
	 SkeletalEntityView.h )
	 
if( WIN32 )
set( SkeletalPluginSources
	 SkeletalEntityView.cpp
	 SkeletalPlugin.rc )
else( WIN32 )
set( SkeletalPluginSources
	 SkeletalEntityView.cpp )
endif( WIN32 )
	 
add_library( SkeletalPlugin SHARED ${SkeletalPluginHeaders} ${SkeletalPluginSources} )

if( WIN32 )
set_property( TARGET SkeletalPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( SkeletalPlugin PROPERTIES COMPILE_FLAGS "-fPIC" 
                                                 LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Visualization 
						 VERSION ${SkeletalPlugin_VERSION_MAJOR}.${SkeletalPlugin_VERSION_MINOR}.${SkeletalPlugin_VERSION_PATCH} 
						 SOVERSION ${SkeletalPlugin_VERSION_MAJOR}.${SkeletalPlugin_VERSION_MINOR}.${SkeletalPlugin_VERSION_PATCH} )
endif( UNIX )
			  
add_dependencies( SkeletalPlugin
				  Core )
				  
target_link_libraries( SkeletalPlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )