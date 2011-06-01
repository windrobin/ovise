# OViSE main

project( OViSE CXX )

cmake_minimum_required( VERSION 2.8 )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Scripts/")

set( Boost_ADDITIONAL_VERSIONS "1.44.0" "1.44" )

if( WIN32 )
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREAD ON )
find_package( Boost 1.44 REQUIRED )
else( WIN32 )
find_package( Boost 1.44 REQUIRED COMPONENTS system filesystem serialization)
endif( WIN32 )

# Ogre
find_package( OGRE 1.7.2 REQUIRED )

# wxWidgets
set( wxWidgets_USE_UNICODE ON )
set( wxWidgets_USE_STATIC ON )
set( wxWidgets_USE_DEBUG OFF )
find_package( wxWidgets 2.9 REQUIRED base core aui propgrid adv )

if( UNIX )
find_package( GTK2 2.10 REQUIRED gtk )
endif( UNIX )

option( PLUGINS_SIMPLE "Build simple mesh plugin" ON )
option( PLUGINS_ROBOT "Build robot plugin" ON )
option( PLUGINS_POINTCLOUD "Build pointcloud plugin" ON )
option( PLUGINS_TRAJECTORY "Build trajectory plugin" ON )
option( PLUGINS_VOODOO "Build Voodoo plugin" OFF )

option( INTERFACES_ILCAS "Build ILCAS interface" ON )
option( INTERFACES_SHAROME "Build SHAROME interface" OFF )
option( INTERFACES_VOODOO "Build VOODOO interface" OFF )

add_subdirectory( Core )
add_subdirectory( Util )
add_subdirectory( CameraControlSystem )
add_subdirectory( Viewer )

if( PLUGINS_SIMPLE )
add_subdirectory( SimplePlugin )
endif()

if( PLUGINS_ROBOT )
add_subdirectory( RobotPlugin )
endif()

if( PLUGINS_POINTCLOUD )
add_subdirectory( PointcloudPlugin )
endif()

if( PLUGINS_VOODOO )
add_subdirectory( VoodooPlugin )
endif()

if( PLUGINS_TRAJECTORY )
add_subdirectory( TrajectoryPlugin )
endif()

if( INTERFACES_ILCAS )
add_subdirectory( ILCASInterface )
endif()

if( INTERFACES_SHAROME )
add_subdirectory( SharomeInterface )
endif()

if( INTERFACES_VOODOO )
add_subdirectory( VoodooInterface )
endif()