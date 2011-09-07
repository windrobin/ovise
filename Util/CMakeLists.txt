# Util

include_directories( ${Boost_INCLUDE_DIR}
					 ${CMAKE_SOURCE_DIR}/Core
					 ${OGRE_INCLUDE_DIRS} )
					 
include( ${wxWidgets_USE_FILE} )
					 
set( UtilHeaders
	AxisDisplay.h
	DefaultInterfaceConfigDlg.h
	Definitions.h
	InterfaceManager.h
	Logging.h
	NetworkInterface.h
	ObjectTitle.h
	OViSEException.h
	PluginBase.h
	PluginManager.h
	SceneLoader.h
	SceneNodeOffset.h
	SelectionBox.h
	Singleton.hpp
	StringConverter.h
	VertexData.h )
	
set( UtilSources
	AxisDisplay.cpp
	DefaultInterfaceConfigDlg.cpp
	InterfaceManager.cpp
	Logging.cpp
	NetworkInterface.cpp
	ObjectTitle.cpp
	OViSEException.cpp
	PluginBase.cpp
	PluginManager.cpp
	SceneNodeOffset.cpp
	SelectionBox.cpp
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
