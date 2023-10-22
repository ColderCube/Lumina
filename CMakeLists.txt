# CMakeList.txt : CMake project for Lumina, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
if (CMAKE_COMPILER_IS_GNUCXX)
  # FIXME: Turn off exceptions, RTTI:
  # -fno-exceptions -fno-rtti
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-common -Woverloaded-virtual -Wno-long-long -Wall -W -Wno-unused-parameter -Wwrite-strings -fno-exceptions -fno-rtti")
elseif (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHs-c-")
  add_definitions("-D_HAS_EXCEPTIONS=0")
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
endif ()

find_package(LLVM REQUIRED CONFIG)

project ("Lumina")

message(${PROJECT_NAME})

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_definitions(${LLVM_DEFINITIONS})

include_directories(${LLVM_INCLUDE_DIRS})

include_directories(Lumina PUBLIC include)
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB LEXER CONFIGURE_DEPENDS "Lexer/*.cpp")

# Add source to this project's executable.
add_executable (Lumina ${SOURCES} ${LEXER})

llvm_map_components_to_libnames(llvm_libs support core irreader ScalarOpts
                                ExecutionEngine OrcJIT native Analysis RuntimeDyld Object InstCombine mcjit
                                )

target_link_libraries(Lumina ${llvm_libs})

# TODO: Add tests and install targets if needed.
