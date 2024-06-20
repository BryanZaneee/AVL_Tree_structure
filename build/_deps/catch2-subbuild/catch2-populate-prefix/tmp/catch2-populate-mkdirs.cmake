# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-src"
  "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-build"
  "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-subbuild/catch2-populate-prefix"
  "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-subbuild/catch2-populate-prefix/tmp"
  "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp"
  "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-subbuild/catch2-populate-prefix/src"
  "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/bryan/Programming_Projects/Resume/AVL_Tree_structure/build/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
