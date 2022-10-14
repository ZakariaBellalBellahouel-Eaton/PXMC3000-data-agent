# CMakeList.txt : CMake project for Smp3050RestApiRequester, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project (SmpDataAgent LANGUAGES C CXX)

# Add source to this project's executable.
add_executable (SmpDataAgent "SmpDataAgent.cpp" "SmpDataAgent.h" "data/entities/firmware.h" "data/entities/hardware.h" "data/entities/settings.h" "data/entities/smpDevice.h" "data/dataAccess/sqlite3DataAccess.h" "data/dataAccess/sqlite3DataAccess.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SmpDataAgent PROPERTY CXX_STANDARD 20)
endif()

# Set C++ standard
#set (CMAKE_CXX_STANDARD 20)
#set (CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# For linux debug, the C & C++ compiler need to be indicated
#set(CMAKE_CXX_COMPILER "/usr/bin/g++" )
#set(CMAKE_C_COMPILER "/usr/bin/gcc" )

# Adding Sqlite3
find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(SmpDataAgent PRIVATE unofficial::sqlite3::sqlite3)

# Add library for Base64 encode for API basic authentication
find_path(CPPCODEC_INCLUDE_DIRS "cppcodec/base32_crockford.hpp")
target_include_directories(SmpDataAgent PRIVATE ${CPPCODEC_INCLUDE_DIRS})

# Add json library
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(SmpDataAgent PRIVATE nlohmann_json::nlohmann_json)

# Add Curl to perfom get request for legacy https 
find_package(CURL REQUIRED)
target_link_libraries(SmpDataAgent PRIVATE curl)

# Add log4cpp
 #find_package(log4cpp CONFIG REQUIRED)
 #target_link_libraries(SmpDataAgent PRIVATE log4cpp::orocos-log4cpp)

# Open SSL
#find_package(OpenSSL REQUIRED)
#target_link_libraries(SmpDataAgent PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# TODO: Add tests and install targets if needed.


 