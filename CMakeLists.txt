# - CmakeLists.txt for building an application

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(CAVS)
#CDEX Active Veto Simulation Frame


# Load some basic macros which are needed later on
include(FindROOT.cmake)
set(INCLUDE_DIRECTORIES
${ROOT_INCLUDE_DIR})
include_directories( ${INCLUDE_DIRECTORIES})
set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR})
link_directories( ${LINK_DIRECTORIES})

#------------------------------------------------------------------------------
# check MPI package...
find_package(MPI REQUIRED)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

find_package(G4mpi REQUIRED)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#------------------------------------------------------------------------------
add_definitions(-DTOOLS_USE_NATIVE_MPI) 

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
		    ${G4mpi_INCLUDE_DIR})


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(CAVS CDEXActiveVetoSimulationFrame.cc ${sources} ${headers})
target_link_libraries(CAVS ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${G4mpi_LIBRARIES} )

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build exMPI03. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(CAVS_SCRIPTS
    vis.mac
    init_vis.mac
  )

foreach(_script ${CAVS_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS CAVS DESTINATION bin)
