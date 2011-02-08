# SharomeInterface

find_package( Sharome REQUIRED )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${Sharome_INCLUDE_DIRS}
					 ${Sharome_INCLUDE_DIRS}/replay
					 ${CMAKE_SOURCE_DIR}/Core
					 ${CMAKE_SOURCE_DIR}/Util )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( SharomeInterfaceHeaders
	 SharomeInterface.h
	 Message.h
	 Connection.h )
	 
set( SharomeInterfaceSources
	 SharomeInterface.cpp )
	 
add_library( SharomeInterface SHARED ${SharomeInterfaceHeaders} ${SharomeInterfaceSources} )

if( WIN32 )
set_property( TARGET SharomeInterface PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
set_target_properties( SharomeInterface PROPERTIES COMPILE_FLAGS "/D_WIN32_WINNT=_WIN32_WINNT_WINXP" )
endif( WIN32 )

if( UNIX )
set_target_properties( SharomeInterface PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET SharomeInterface PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
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