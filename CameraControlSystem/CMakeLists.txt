include_directories( ${OGRE_INCLUDE_DIRS}
					 include )
					 
set( CCS_Headers
	 include/CCSBasicCameraModes.h
	 include/CCSCameraControlSystem.h
	 include/CCSFastDelegate.h
	 include/CCSFastDelegateBind.h
	 include/CCSFreeCameraMode.h
	 include/CCSOrbitalCameraMode.h
	 include/CCSPrerequisites.h )
	 
set( CCS_Sources
	 src/CCSBasicCameraModes.cpp
     src/CCSCameraControlSystem.cpp
     src/CCSFreeCameraMode.cpp
     src/CCSOrbitalCameraMode.cpp
     src/CCSPrerequisites.cpp )
	 
	 
add_library ( CCS STATIC ${CCS_Headers} ${CCS_Sources})

install( TARGETS CCS ARCHIVE DESTINATION lib )