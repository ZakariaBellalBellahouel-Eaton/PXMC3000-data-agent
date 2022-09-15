# CMakeList.txt : CMake project for Smp3050RestApiRequester, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project (SmpHttpClient)

# Add source to this project's executable.
add_executable (SmpHttpClient "SmpHttpClient.cpp" "SmpHttpClient.h" "data/entities/firmware.h" "data/entities/hardware.h" "data/entities/settings.h" "data/entities/smpDevice.h" "data/dataAccess/Sqlite3DataAccess.h" "data/dataAccess/Sqlite3DataAccess.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SmpHttpClient PROPERTY CXX_STANDARD 20)
endif()

# Set C++ standard
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# TODO: Add tests and install targets if needed.

# Adding cpprestsdk 
find_package(cpprestsdk CONFIG REQUIRED)
target_link_libraries(SmpHttpClient PRIVATE cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal)

# Adding Sqlite3
find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(SmpHttpClient PRIVATE unofficial::sqlite3::sqlite3)

# Add library for Base64 encode for API basic authentication
find_path(CPPCODEC_INCLUDE_DIRS "cppcodec/base32_crockford.hpp")
target_include_directories(SmpHttpClient PRIVATE ${CPPCODEC_INCLUDE_DIRS})

# Add json library
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(SmpHttpClient PRIVATE nlohmann_json::nlohmann_json)