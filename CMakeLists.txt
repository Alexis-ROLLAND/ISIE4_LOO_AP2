cmake_minimum_required(VERSION 3.4)		# never set less 3.4 min version
project(TestSensor)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    message(STATUS "Ccache détecté : ${CCACHE_PROGRAM}")
else()
    message(STATUS "Ccache non trouvé")
endif()


set(CMAKE_CXX_STANDARD 23)  # We're using C++23 standard :)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Désactiver les extensions spécifiques au compilateur
set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")


find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")

# Build type is debug by default
# call cmake .. -DCMAKE_BUILD_TYPE=Release to change to relase
# call cmake .. -DCMAKE_BUILD_TYPE=Debug to revert to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug, Release, etc.)" FORCE)
endif()

add_compile_options(-Wshadow -Wnon-virtual-dtor -Wold-style-cast)

# Définir des options de compilation pour tous les compilateurs
add_compile_options(-Wall -Wextra -Wpedantic)

# Ajout de flags spécifiques pour GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(SANITIZE_FLAGS "-fsanitize=undefined") # Choisissez vos sanitizers ici (pas de leak ni address car wxWidgets est plein de leaks (sic) )
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(${SANITIZE_FLAGS} -fno-omit-frame-pointer -g)
    add_link_options(${SANITIZE_FLAGS})
  endif()
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")             # Debug : Optimisation légère pour le débogage
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")     # Release : Optimisation maximale sans symboles de debug

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")


include_directories(include)

add_executable(testSensor src/testSensor.cpp src/Sensor.cpp)




