// Smp3050RestApiRequester.cpp : Defines the entry point for the application.

#include "SmpHttpClient.h"

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace smp::data::dataAccess;
using namespace smp::data::entities;

// Namepaces aliases 
namespace jsonLibrary = web::json;
namespace httpLibrary = web::http;

bool loadConfiguration();


int main()
{
	// TODO : All this constate will be replaced by params
	string stringJsonSMPIdsID = "IDs";
	string stringJsonSMPInformationID = "Informations";
	const wstring jsonSMPIdsID(wstring(stringJsonSMPIdsID.begin(), stringJsonSMPIdsID.end()));
	const wstring jsonSMPInformationID(wstring(stringJsonSMPInformationID.begin(), stringJsonSMPInformationID.end()));
	// SMP IP adress
	string stringSmpBasicUri = "https://10.106.88.181/";
	const uri smpBasicUri(wstring(stringSmpBasicUri.begin(), stringSmpBasicUri.end()));
	// TO by encrypted in param file
	const string username = "security";
	const string password = "Security8*";
	// Authorization header key
	const wstring stringAutorizationHeaderKey = L"Authorization";
	const http_headers::key_type autorizationHeaderKey = stringAutorizationHeaderKey.c_str();
	//SMP entity
	//smpDevice smpDeviceObject;
	// SMP Configuration Database path
	const char* configurationDatabaseFullPath = "C:\\Users\\e0718027\\source\\repos\\SmpHttpClient\\SmpHttpClient\\Database\\SMPConfiguration.db";
	//const char* getSMPDeviceIDUri = "api/dashboard/v1/name-plate-informations/";
	const utility::string_t getSMPDeviceIDUri = U("api/dashboard/v1/name-plate-informations/");
	// String array that will contains the smp Ids 
	utility::string_t* smpDeviceIds = nullptr;
	// Variable to store the dynamic size of the smpDeviceIds array
	int smpDeviceIdsSize = 0;
	// Variable that will handle the APi responses
	pplx::task<httpLibrary::http_response> response;
	// HTTP Client configuration
	http_client_config config;
	// Http request Header Autorization value
	string authorizationHeaderValue;
	config.set_validate_certificates(false);
	// Sqlite3DataAccess to manipulate all the data with database layer 
	dataAccess::sqlite3DataAccess smpSqlite3DataAccess(configurationDatabaseFullPath);

	// HTTP Client
	http_client client(smpBasicUri, config);
	//Http get request 
	http_request getRequest(httpLibrary::methods::GET);

	// Setup the get request Authorization
	getRequest.headers().add(autorizationHeaderKey.c_str(), ("Basic " + cppcodec::base64_rfc4648::encode(username + ":" + password)).c_str());
	//  Step 1 : get the SMP device Ids dynamically & get the json
	try
	{
		int arrayIterator = 0;
		getRequest.set_request_uri(getSMPDeviceIDUri);
		response = client.request(getRequest);
		if (response.get().status_code() != 200)
		{
			// TO DO : raise an exception
			throw;
		}
		// Extract the SMP Ids list from the returned JSON
		jsonLibrary::object idsJsonResult = response.get().extract_json().get().as_object();
		jsonLibrary::array idsJsonValue = idsJsonResult.at(jsonSMPIdsID).as_array();
		list<smpDevice> smpDeviceList = {};
		// Loop throw each identifier and get its data
		for (jsonLibrary::value& jsonValueIterator : idsJsonValue)
		{
			getRequest.set_request_uri(getSMPDeviceIDUri + jsonValueIterator.as_string());
			response = client.request(getRequest);
			if (response.get().status_code() != 200)
			{
				// TO DO : raise an exception
				throw;
			}
			jsonLibrary::object smpInformationJsonResult = response.get().extract_json().get().as_object().at(jsonSMPInformationID).as_object();
			smpDeviceList.emplace_back(smpDevice{
				smpInformationJsonResult.at(L"ID").as_string(),
				smpInformationJsonResult.at(L"Hardware").as_object().at(L"Model").as_string(),
				smpInformationJsonResult.at(L"Hardware").as_object().at(L"SerialNumber").as_string(),
				smpInformationJsonResult.at(L"Firmware").as_object().at(L"BootstrapVersion").as_string(),
				smpInformationJsonResult.at(L"Firmware").as_object().at(L"OsVersion").as_string(),
				smpInformationJsonResult.at(L"Firmware").as_object().at(L"ApplicationVersion").as_string(),
				smpInformationJsonResult.at(L"Settings").as_object().at(L"Name").as_string(),
				smpInformationJsonResult.at(L"Settings").as_object().at(L"Description").as_string(),
				smpInformationJsonResult.at(L"Settings").as_object().at(L"Company").as_string(),
				smpInformationJsonResult.at(L"Settings").as_object().at(L"Region").as_string(),
				smpInformationJsonResult.at(L"Settings").as_object().at(L"Substation").as_string(),
				smpInformationJsonResult.at(L"Settings").as_object().at(L"Filename").as_string(),
				smpInformationJsonResult.at(L"Settings").as_object().at(L"FileDate").as_string(),
				smpInformationJsonResult.at(L"Settings").as_object().at(L"FileCRC").as_integer()
				});

			try
			{
				// Store the data in the DataBase ( Sqlite at the moment of writing this comment )
				// Initialize the Database
				smpSqlite3DataAccess.initializeSmpDeviceBatabase();
				// Save the data
				smpSqlite3DataAccess.upsertSmpDevice(smpDeviceList.back());
			}
			catch (const exception ex)
			{
				cerr << "Error saving smpDevice data: " << ex.what() << endl;
			}
		}

	}
	catch (const std::exception ex)
	{
		wcout << ex.what();
	}

	//Free memory
	delete smpDeviceIds;

	return 0;
}

// Implementation section

bool loadConfiguration() {
	ifstream configurationFile(CONFIG_FILE_PATH);
	if (!configurationFile.is_open())
	{
		cerr << "Fatal error, configuration file missing." << endl;
		return false;
	}
	return true;
}
