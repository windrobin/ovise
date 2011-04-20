# ILCASInterface

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core
					 ${CMAKE_SOURCE_DIR}/Util )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( VoodooInterfaceHeaders
	 VoodooInterface.h
	 Connection.hpp
	 VoodooParser.hpp )
	 
set( VoodooInterfaceSources
	 VoodooInterface.cpp
	 VoodooParser.cpp )
	 
add_library( VoodooInterface SHARED ${VoodooInterfaceHeaders} ${VoodooInterfaceSources} )

if( WIN32 )
set_property( TARGET VoodooInterface PROPERTY RUNTIME_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
set_target_properties( VoodooInterface PROPERTIES COMPILE_FLAGS "/D_WIN32_WINNT=_WIN32_WINNT_WINXP" )
endif( WIN32 )

if( UNIX )
set_target_properties( VoodooInterface PROPERTIES COMPILE_FLAGS "-fPIC" )
set_property( TARGET VoodooInterface PROPERTY LIBRARY_OUTPUT_DIRECTORY
			  ${CMAKE_BINARY_DIR}/Plugins/Interfaces )
endif( UNIX )
			  
add_dependencies( VoodooInterface
				  Core )
				  
target_link_libraries( VoodooInterface
					   Core
					   Util
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )