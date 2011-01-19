# OViSE main

project( OViSE CXX )

set( Boost_ADDITIONAL_VERSIONS "1.44.0" "1.44" )

if( WIN32 )
set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREAD ON )
find_package( Boost 1.44 REQUIRED )
else( WIN32 )
find_package( Boost 1.44 REQUIRED COMPONENTS system filesystem )
endif( WIN32 )

