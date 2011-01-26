# Util

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIRS} )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( UtilHeaders
	InterfaceManager.h
	Logging.h
	NetworkInterface.h
	ObjectTitle.h
	OViSEException.h
	SceneNodeOffset.h
	StringConverter.h )
	
set( UtilSources
	InterfaceManager.cpp
	Logging.cpp
	NetworkInterface.cpp
	ObjectTitle.cpp
	OViSEException.cpp
	SceneNodeOffset.cpp
	StringConverter.cpp )
	
add_library( Util STATIC ${UtilHeaders} ${UtilSources} )

if( WIN32 )
set_target_properties( Util PROPERTIES COMPILE_FLAGS "/D_WIN32_WINNT=_WIN32_WINNT_WINXP" )
else( WIN32 )
set_target_properties( Util PROPERTIES COMPILE_FLAGS "-fPIC" )
endif( WIN32 )

target_link_libraries( Util
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )