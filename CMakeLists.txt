cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0003 NEW)

project(SC11Demo)

if("${PROJECT_SOURCE_DIR}"  STREQUAL "${PROJECT_BINARY_DIR}")
  message(FATAL_ERROR "SC11Demo requires an out of source Build.")
endif()

include(ParaViewConfig.cmake)
include(MPICHConfig.cmake)

set(SC11Demo_LIB_INSTALL_PATH
  "${CMAKE_INSTALL_PREFIX}/lib/paraview-${PARAVIEW_VERSION_MAJOR}.${PARAVIEW_VERSION_MINOR}"
  )

# Server manager wrapped sources.
message(STATUS "Building the SC11 demo")
set(SM_CXX_SOURCES
  ${SM_CXX_SOURCES}
  vtkSC11DemoAnnotation.cxx
  vtkSC11DemoExtentTranslator.cxx
  vtkSC11DemoReader.cxx
  )

# Un-wrapped sources
set(CXX_SOURCES
  CartesianExtent.cxx
  FsUtils.cxx
  postream.cxx
  PrintUtils.cxx
  )

if(PARAVIEW_BUILD_QT_GUI)
  message(STATUS "Including custom panels.")
  set(_IFACES)
  set(_IFACE_SRCS)
  # Qt custom panels
  QT4_WRAP_CPP(MOC_SRCS pqSQHemisphereSource.h)
  QT4_WRAP_UI(UI_SRCS pqSQHemisphereSourceForm.ui)

  QT4_WRAP_CPP(MOC_SRCS pqSC11DemoReader.h)
  ADD_PARAVIEW_OBJECT_PANEL(
    IFACES IFACE_SRCS
    CLASS_NAME pqSC11DemoReader
    XML_NAME vtkSC11DemoReader
    XML_GROUP sources)
  set(_IFACES ${_IFACES} ${IFACES})
  set(_IFACE_SRCS ${_IFACE_SRCS} ${IFACE_SRCS})

  set (CXX_SOURCES
    ${CXX_SOURCES}
    ${MOC_SRCS}
    ${UI_SRCS}
    ${_IFACE_SRCS}
    pqSC11DemoReader.cxx
    )
endif (PARAVIEW_BUILD_QT_GUI)

set (CLIENT_XML
  SC11DemoClientReaders.xml
  )

# Generate the plugin, servermanager and wrapped language bindings.
add_paraview_plugin(
  SC11Demo "11.02"
  GUI_INTERFACES ${_IFACES}
  SERVER_MANAGER_SOURCES ${SM_CXX_SOURCES}
  SERVER_MANAGER_XML SC11DemoServerManager.xml
  GUI_RESOURCE_FILES ${CLIENT_XML}
  SOURCES ${CXX_SOURCES})

install(TARGETS SC11Demo DESTINATION ${SC11Demo_LIB_INSTALL_PATH})
