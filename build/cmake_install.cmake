<<<<<<< HEAD
# Install script for directory: /home/local.isima.fr/vadinardo/TP_GeoAlgo
=======
# Install script for directory: /home/local.isima.fr/vicanhotod/TP_GeoAlgo
>>>>>>> 87af73cb9093507404d7822fea600c015c0fb4a5

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
<<<<<<< HEAD
  # Include the install script for the subdirectory.
  include("/home/local.isima.fr/vadinardo/TP_GeoAlgo/build/src/cmake_install.cmake")
=======
  # Include the install script for each subdirectory.
  include("/home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/src/cmake_install.cmake")

>>>>>>> 87af73cb9093507404d7822fea600c015c0fb4a5
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/home/local.isima.fr/vadinardo/TP_GeoAlgo/build/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/home/local.isima.fr/vicanhotod/TP_GeoAlgo/build/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 87af73cb9093507404d7822fea600c015c0fb4a5
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
