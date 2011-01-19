# Viewer

include_directories( ${Boost_INCLUDE_DIR}
					 ${OGRE_INCLUDE_DIRS}
					 ${CMAKE_SOURCE_DIR}/Core 
					 ${CMAKE_SOURCE_DIR}/Util )
					 
include( ${wxWidgets_USE_FILE} )

set( ViewerHeaders
	 AddMeshDialog.h
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
	 SceneHandling.h
	 SceneTree.h )
	 
set( ViewerSources
	 AddMeshDialog.cpp
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
	 SceneHandling.cpp
	 SceneTree.cpp )
	 
add_executable( Viewer WIN32 ${ViewerHeaders} ${ViewerSources} )

set_property( TARGET Viewer PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
if( WIN32 )
set_target_properties( Viewer PROPERTIES COMPILE_FLAGS "/D_CRT_SECURE_NO_WARNINGS" )
endif()

add_dependencies( Viewer
				  Core
				  Util )
				  
target_link_libraries( Viewer
					   Core
					   Util
					   ${Boost_LIBRARIES}
					   ${OGRE_LIBRARIES}
					   ${wxWidgets_LIBRARIES} )