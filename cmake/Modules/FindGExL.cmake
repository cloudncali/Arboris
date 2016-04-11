# - Try to find GExL
# Once done this will define
#  GExL_FOUND - System has GExL
#  GExL_INCLUDE_DIRS - The GExL include directories
#  GExL_LIBRARIES - The libraries needed to use GExL
#  GExL_DEFINITIONS - Compiler switches required for using GExL
# find the GExL include directory
find_path(GExL_INCLUDE_DIR GExL/Config.hpp
  PATH_SUFFIXES include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/
  /usr/
  /sw          # Fink
  /opt/local/  # DarwinPorts
  /opt/csw/    # Blastwave
  /opt/
  ${GExLDIR}
  $ENV{GExLDIR})
  
find_library(GExL_LIBRARY NAMES  gexl-s libgexl-s
  PATH_SUFFIXES lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/
  /usr/
  /sw          # Fink
  /opt/local/  # DarwinPorts
  /opt/csw/    # Blastwave
  /opt/
  ${GExLDIR}
  $ENV{GExLDIR} )
find_library(GExL_DEBUG_LIBRARY NAMES  gexl-s-d libgexl-s-d
  PATH_SUFFIXES lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/
  /usr/
  /sw          # Fink
  /opt/local/  # DarwinPorts
  /opt/csw/    # Blastwave
  /opt/
  ${GExLDIR}
  $ENV{GExLDIR} )
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set GExL_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(GExL  DEFAULT_MSG
                                  GExL_LIBRARY GExL_INCLUDE_DIR)