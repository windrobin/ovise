# ILCASInterface

set( ILCASPlugin_VERSION_MAJOR 0 )
set( ILCASPlugin_VERSION_MINOR 1 )
set( ILCASPlugin_VERSION_PATCH 0 )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ILCASPlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/ILCASPlugin.rc )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core
					 ${CMAKE_SOURCE_DIR}/Util )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( ILCASInterfaceHeaders
	 ILCASInterface.h
	 SocketMessage.h )
	 
if( WIN32 )
set( ILCASInterfaceSources
	 ILCASInterface.cpp
	 SocketMessage.cpp
	 ILCASPlugin.rc )
else( WIN32 )
set( ILCASInterfaceSources
	 ILCASInterface.cpp
	 SocketMessage.cpp )
endif( WIN32 )
	 
add_library( ILCASInterface SHARED ${ILCASInterfaceHeaders} ${ILCASInterfaceSources} )

if( WIN32 )
set_property( TARGET ILCASInterface PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
set_target_properties( ILCASInterface PROPERTIES COMPILE_FLAGS "/D_WIN32_WINNT=_WIN32_WINNT_WINXP" )
endif( WIN32 )

if( UNIX )
set_target_properties( ILCASInterface PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET ILCASInterface PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
endif( UNIX )
			  
add_dependencies( ILCASInterface
				  Core )
				  
target_link_libraries( ILCASInterface
					   Core
					   Util
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )