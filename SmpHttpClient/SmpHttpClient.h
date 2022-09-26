// Smp3050RestApiRequester.h : Include file for standard system include files,
// or project specific include files.

#pragma once

// Curl Library to perform/handle Http/Https request 
#include <curl/curl.h>

// Json Library
#include <nlohmann/json.hpp>

// Library for decoding
#include <cppcodec/base64_rfc4648.hpp>

// Library for Json that may be used to compare performance
//#include <nlohmann/json.hpp>

// Data structure to support the SMP Rest API messages
#include "data/entities/smpDevice.h"
#include "data/dataAccess/sqlite3DataAccess.h"

// Standards libraries
#include <iostream>
#include <fstream>
#include <list>

//Libraries for Linux Daemon
#include <unistd.h> // for fork
#include <stdlib.h> // for exit
#include <sys/stat.h> //for umark
#include <sys/types.h>
#include <syslog.h> // require installation of log4cpp
#include <signal.h>

// Library for Chrono
#include <chrono>

// Library to control the thread
#include <thread>


// Program contants

constexpr auto CONFIG_FILE_PATH = "./config/SmpHttpClient.config";;
