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
include(SelectLibraryConfigurations)

# Sharome base dir
set( Sharome_BASE_DIR $ENV{SHAROME_HOME})

# Include dir
find_path(Sharome_INCLUDE_DIR
  NAMES Result.h
  PATHS ${Sharome_BASE_DIR}/include
)

# Finally the libraries itself
find_library(Sharome_LIBRARY_DEBUG
	NAMES SharomeLegacyClient
	PATHS ${Sharome_BASE_DIR}/lib/Debug
)
find_library(Sharome_LIBRARY_RELEASE
	NAMES SharomeLegacyClient
	PATHS ${Sharome_BASE_DIR}/lib/Release
)

select_library_configurations( Sharome )

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set( Sharome_PROCESS_INCLUDES Sharome_INCLUDE_DIR )
set( Sharome_PROCESS_LIBS Sharome_LIBRARY )
libfind_process( Sharome )