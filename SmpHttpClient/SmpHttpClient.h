// Smp3050RestApiRequester.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <cpprest/http_client.h>
#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include <cppcodec/base64_rfc4648.hpp>
#include <nlohmann/json.hpp>
#include "data/entities/smpDevice.h"
#include "data/dataAccess/sqlite3DataAccess.h"
#include <iostream>
#include <fstream>

// Program contants

constexpr auto CONFIG_FILE_PATH = "./config/SmpHttpClient.config";;
