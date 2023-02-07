# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.1...3.15)

<<<<<<< HEAD
project( 3 )
=======
project( src )
>>>>>>> 87af73cb9093507404d7822fea600c015c0fb4a5


# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )

  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()  

endif()


# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )

  message(STATUS "This project requires the Boost library, and will not be compiled.")

  return()  

endif()

# include for local directory

# include for local package


# Creating entries for all C++ files with "main" routine
# ##########################################################


create_single_source_cgal_program( "genre.cpp" )

create_single_source_cgal_program( "measures.cpp" )

<<<<<<< HEAD
create_single_source_cgal_program( "seuillage.cpp" )

=======
>>>>>>> 87af73cb9093507404d7822fea600c015c0fb4a5

