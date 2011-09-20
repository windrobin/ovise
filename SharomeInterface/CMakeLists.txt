# SharomeInterface

find_package( Sharome REQUIRED )

set( SharomePlugin_VERSION_MAJOR 0 )
set( SharomePlugin_VERSION_MINOR 1 )
set( SharomePlugin_VERSION_PATCH 0 )

if( WIN32 )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/SharomePlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/SharomePlugin.rc )
endif( WIN32 )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${Sharome_INCLUDE_DIR}
					 ${Sharome_INCLUDE_DIR}/replay
					 ${CMAKE_SOURCE_DIR}/Core
					 ${CMAKE_SOURCE_DIR}/Util )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( SharomeInterfaceHeaders
	 SharomeInterface.h
	 Message.h
	 Connection.h )

if( WIN32 )
set( SharomeInterfaceSources
	 SharomePlugin.rc
	 SharomeInterface.cpp )
else( WIN32 )
set( SharomeInterfaceSources
	 SharomeInterface.cpp )
endif( WIN32 )
	 
add_library( SharomeInterface SHARED ${SharomeInterfaceHeaders} ${SharomeInterfaceSources} )

if( WIN32 )
set_target_properties( SharomeInterface PROPERTIES COMPILE_FLAGS "/D_WIN32_WINNT=_WIN32_WINNT_WINXP"
                                                   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
endif( WIN32 )

if( UNIX )
set_target_properties( SharomeInterface PROPERTIES COMPILE_FLAGS "-fPIC"
                                                   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Interfaces 
						   VERSION ${SharomePlugin_VERSION_MAJOR}.${SharomePlugin_VERSION_MINOR}.${SharomePlugin_VERSION_PATCH} 
						   SOVERSION ${SharomePlugin_VERSION_MAJOR}.${SharomePlugin_VERSION_MINOR}.${SharomePlugin_VERSION_PATCH} )
endif( UNIX )
			  
add_dependencies( SharomeInterface
				  Core )
				  
target_link_libraries( SharomeInterface
					   Core
					   Util
					   ${Sharome_LIBRARIES}
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )
					   
if( WIN32 )
install( TARGETS SharomeInterface RUNTIME CONFIGURATIONS Debug DESTINATION Plugins/Interfaces/Debug )
install( TARGETS SharomeInterface RUNTIME CONFIGURATIONS Release DESTINATION Plugins/Interfaces/Release )
elseif( UNIX )
install( TARGETS SharomeInterface LIBRARY DESTINATION Plugins/Interfaces )
endif()