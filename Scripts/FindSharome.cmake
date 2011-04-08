# - Try to find Sharome
# Once done, this will define
#
#  Sharome_FOUND - system has Sharome
#  Sharome_INCLUDE_DIRS - the Sharome include directories
#  Sharome_LIBRARIES - link these to use Sharome
#
# Currently this only searches in the home directory set by
# the environment variable SHAROME_HOME (this is the dir you
# should specify as prefix when installing Sharome)

include(LibFindMacros)

# Include dir
find_path(Sharome_INCLUDE_DIR
  NAMES Result.h
  PATHS $ENV{SHAROME_HOME}/include
)

# Finally the libraries itself
find_library(Util_LIBRARY
  NAMES Util
  PATHS $ENV{SHAROME_HOME}/lib
)

find_library(Mem_LIBRARY
  NAMES Mem
  PATHS $ENV{SHAROME_HOME}/lib
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set( Sharome_PROCESS_INCLUDES Sharome_INCLUDE_DIR )
set( Sharome_PROCESS_LIBS Util_LIBRARY Mem_LIBRARY )
libfind_process( Sharome )