#
# XIP
#

superbuild_include_once()

set(proj XIP)

set(${proj}_DEPENDENCIES "")

superbuild_include_dependencies(PROJECT_VAR proj)

if(${CMAKE_PROJECT_NAME}_USE_SYSTEM_${proj})
  message(FATAL_ERROR "Enabling ${CMAKE_PROJECT_NAME}_USE_SYSTEM_${proj} is not supported !")
endif()

# Sanity checks
if(DEFINED XIP_DIR AND NOT EXISTS ${XIP_DIR})
  message(FATAL_ERROR "XIP_DIR variable is defined but corresponds to non-existing directory")
endif()


if(NOT DEFINED XIP_DIR)

  set(location_args )
  if(${proj}_URL)
    set(location_args URL ${${proj}_URL})
  else()
    set(location_args SVN_REPOSITORY "https://collab01a.scr.siemens.com/svn/xip/releases/latest"
                      SVN_USERNAME "anonymous")
  endif()

  ExternalProject_Add(${proj}
    ${${proj}_EXTERNAL_PROJECT_ARGS}
    SOURCE_DIR ${CMAKE_BINARY_DIR}/${proj}
    BINARY_DIR ${proj}-build
    PREFIX ${proj}${ep_suffix}
    ${location_args}
    INSTALL_COMMAND ""
    CMAKE_CACHE_ARGS
      ${ep_common_cache_args}
      -DHAS_VTK:BOOL=OFF
      -DHAS_ITK:BOOL=OFF
    DEPENDS
      ${${proj}_DEPENDENCIES}
    )
  set(XIP_DIR ${CMAKE_BINARY_DIR}/${proj}-build)

else()
  superbuild_add_empty_external_project(${proj} "${${proj}_DEPENDENCIES}")
endif()

mark_as_superbuild(
  VARS XIP_DIR:PATH
  LABELS "FIND_PACKAGE"
  )
