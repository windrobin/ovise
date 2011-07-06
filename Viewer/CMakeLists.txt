# Viewer

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
	 
add_executable( Viewer WIN32 ${ViewerHeaders} ${ViewerSources} )

set_property( TARGET Viewer PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set_target_properties( Viewer PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} SOVERSION ${${PROJECT_NAME}_SOVERSION} )
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