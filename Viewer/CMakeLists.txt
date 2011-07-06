# Viewer

set( Viewer_VERSION_MAJOR 0 )
set( Viewer_VERSION_MINOR 5 )
set( Viewer_VERSION_PATCH 0 )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/Viewer.rc.in
				${CMAKE_CURRENT_SOURCE_DIR}/Viewer.rc )

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIRS}
					 ${GTK2_INCLUDE_DIRS}
					 ${CMAKE_SOURCE_DIR}/Core 
					 ${CMAKE_SOURCE_DIR}/Util
					 ${CMAKE_SOURCE_DIR}/CameraControlSystem/include )
					 
include( ${wxWidgets_USE_FILE} )

set( ViewerHeaders
	 AppContext.h
	 Application.h
	 AttributeView.h
	 DotSceneManager.h
	 InputHandler.h
	 LogListener.h
	 MainFrame.h
	 MainFrameBase.h
	 OgreWindow.h
	 PathConfigDialog.h
	 PathProvider.h
	 PluginManager.h
	 SceneHandling.h
	 SceneTree.h )
	 
set( ViewerSources
	 AppContext.cpp
	 Application.cpp
	 AttributeView.cpp
	 DotSceneManager.cpp
	 InputHandler.cpp
	 LogListener.cpp
	 MainFrame.cpp
	 MainFrameBase.cpp
	 OgreWindow.cpp
	 PathConfigDialog.cpp
	 PathProvider.cpp
	 PluginManager.cpp
	 SceneHandling.cpp
	 SceneTree.cpp )
	 
if( WIN32 )
set( ViewerSources ${ViewerSources} Viewer.rc )
endif( WIN32 )
	 
add_executable( Viewer WIN32 ${ViewerHeaders} ${ViewerSources} )

set_target_properties( Viewer PROPERTIES VERSION ${Viewer_VERSION_MAJOR}.${Viewer_VERSION_MINOR}.${Viewer_VERSION_PATCH} 
										 SOVERSION ${Viewer_VERSION_MAJOR}.${Viewer_VERSION_MINOR}.${Viewer_VERSION_PATCH}
										 RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
if( WIN32 )
set_target_properties( Viewer PROPERTIES COMPILE_FLAGS "/D_CRT_SECURE_NO_WARNINGS" )
endif()

add_dependencies( Viewer
				  Core
				  Util
				  CCS )
				  
target_link_libraries( Viewer
					   Core
					   Util
					   CCS
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES}
					   ${GTK2_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )