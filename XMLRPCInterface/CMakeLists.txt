# XMLRPCInterface

set( XMLRPCPlugin_VERSION_MAJOR 0 )
set( XMLRPCPlugin_VERSION_MINOR 1 )
set( XMLRPCPlugin_VERSION_PATCH 0 )

if( WIN32 )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/XMLRPCPlugin.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/XMLRPCPlugin.rc )
endif( WIN32 )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core
					 ${CMAKE_SOURCE_DIR}/Util )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( XMLRPCInterfaceHeaders
	 XMLRPCInterface.h
	 XMLRPCMessageHandler.h )
	 
if( WIN32 )
set( XMLRPCInterfaceSources
	 XMLRPCInterface.cpp
         HTTPHeader.h
         HTTPReply.h
         HTTPReply.cpp
         HTTPRequest.h
         HTTPRequstParser.h
         HTTPRequestParser.cpp
	 XMLRPCMessageHandler.cpp
	 XMLRPCPlugin.rc )
else( WIN32 )
set( XMLRPCInterfaceSources
	 XMLRPCInterface.cpp
         HTTPHeader.h
         HTTPReply.h
         HTTPReply.cpp
         HTTPRequest.h
         HTTPRequestParser.h
         HTTPRequestParser.cpp
	 XMLRPCMessageHandler.cpp )
endif( WIN32 )
	 
add_library( XMLRPCInterface SHARED ${XMLRPCInterfaceHeaders} ${XMLRPCInterfaceSources} )

if( WIN32 )
set_property( TARGET XMLRPCInterface PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
set_target_properties( XMLRPCInterface PROPERTIES COMPILE_FLAGS "/D_WIN32_WINNT=_WIN32_WINNT_WINXP" )
endif( WIN32 )

if( UNIX )
set_target_properties( XMLRPCInterface PROPERTIES COMPILE_FLAGS "-fPIC"
                                                 LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Plugins/Interfaces 
						 VERSION ${XMLRPCPlugin_VERSION_MAJOR}.${XMLRPCPlugin_VERSION_MINOR}.${XMLRPCPlugin_VERSION_PATCH} 
						 SOVERSION ${XMLRPCPlugin_VERSION_MAJOR}.${XMLRPCPlugin_VERSION_MINOR}.${XMLRPCPlugin_VERSION_PATCH} )
endif( UNIX )
			  
add_dependencies( XMLRPCInterface
				  Core )
				  
target_link_libraries( XMLRPCInterface
					   Core
					   Util
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )
					   
if( WIN32 )
install( TARGETS XMLRPCInterface RUNTIME CONFIGURATIONS Debug DESTINATION Plugins/Interfaces/Debug )
install( TARGETS XMLRPCInterface RUNTIME CONFIGURATIONS Release DESTINATION Plugins/Interfaces/Release )
elseif( UNIX )
install( TARGETS XMLRPCInterface LIBRARY DESTINATION Plugins/Interfaces )
endif()
