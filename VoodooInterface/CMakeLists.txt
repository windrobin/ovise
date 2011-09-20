# VoodooInterface

set( VoodooInterfacePlugin_VERSION_MAJOR 0 )
set( VoodooInterfacePlugin_VERSION_MINOR 1 )
set( VoodooInterfacePlugin_VERSION_PATCH 0 )

if( WIN32 )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/VoodooInterfacePlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/VoodooInterfacePlugin.rc )
endif( WIN32 )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core
					 ${CMAKE_SOURCE_DIR}/Util )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( VoodooInterfaceHeaders
	 VoodooInterface.h
	 Connection.hpp
	 VoodooParser.hpp )
	 
if( WIN32 )
set( VoodooInterfaceSources
	 VoodooInterface.cpp
	 VoodooParser.cpp
	 VoodooInterfacePlugin.rc )
else( WIN32 )
set( VoodooInterfaceSources
	 VoodooInterface.cpp
	 VoodooParser.cpp )
endif( WIN32 )
	 
add_library( VoodooInterface SHARED ${VoodooInterfaceHeaders} ${VoodooInterfaceSources} )

if( WIN32 )
set_target_properties( VoodooInterface PROPERTIES COMPILE_FLAGS "/D_WIN32_WINNT=_WIN32_WINNT_WINXP"
                                                  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
endif( WIN32 )

if( UNIX )
set_target_properties( VoodooInterface PROPERTIES COMPILE_FLAGS "-fPIC" 
                                                  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Interfaces 
						  VERSION ${VoodooInterfacePlugin_VERSION_MAJOR}.${VoodooInterfacePlugin_VERSION_MINOR}.${VoodooInterfacePlugin_VERSION_PATCH} 
						  SOVERSION ${VoodooInterfacePlugin_VERSION_MAJOR}.${VoodooInterfacePlugin_VERSION_MINOR}.${VoodooInterfacePlugin_VERSION_PATCH} )
endif( UNIX )
			  
add_dependencies( VoodooInterface
				  Core )
				  
target_link_libraries( VoodooInterface
					   Core
					   Util
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )
					   
if( WIN32 )
install( TARGETS VoodooInterface RUNTIME CONFIGURATIONS Debug DESTINATION Plugins/Interfaces/Debug )
install( TARGETS VoodooInterface RUNTIME CONFIGURATIONS Release DESTINATION Plugins/Interfaces/Release )
elseif( UNIX )
install( TARGETS VoodooInterface LIBRARY DESTINATION Plugins/Interfaces )
endif()