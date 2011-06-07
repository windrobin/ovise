# SkeletalPlugin

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core )
					 
set( SkeletalPluginHeaders
	 SkeletalEntityView.h )
	 
set( SkeletalPluginSources
	 SkeletalEntityView.cpp )
	 
add_library( SkeletalPlugin SHARED ${SkeletalPluginHeaders} ${SkeletalPluginSources} )

if( WIN32 )
set_property( TARGET SkeletalPlugin PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( WIN32 )

if( UNIX )
set_target_properties( SkeletalPlugin PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET SkeletalPlugin PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Visualization )
endif( UNIX )
			  
add_dependencies( SkeletalPlugin
				  Core )
				  
target_link_libraries( SkeletalPlugin
					   Core
					   ${OGRE_LIBRARIES}
					   ${Boost_LIBRARIES} )