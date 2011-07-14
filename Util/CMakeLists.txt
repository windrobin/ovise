# Util

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIRS} )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( UtilHeaders
	DefaultInterfaceConfigDlg.h
	InterfaceManager.h
	Logging.h
	NetworkInterface.h
	ObjectTitle.h
	OViSEException.h
	PluginBase.h
	SceneLoader.h
	SceneNodeOffset.h
	Singleton.hpp
	StringConverter.h
	VertexData.h )
	
set( UtilSources
	DefaultInterfaceConfigDlg.cpp
	InterfaceManager.cpp
	Logging.cpp
	NetworkInterface.cpp
	ObjectTitle.cpp
	OViSEException.cpp
	PluginBase.cpp
	SceneNodeOffset.cpp
	StringConverter.cpp
	VertexData.cpp )
	
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
