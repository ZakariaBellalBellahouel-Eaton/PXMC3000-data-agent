// Smp3050RestApiRequester.cpp : Defines the entry point for the application.

#include "SmpDataAgent.h"

using namespace std;
using namespace smp::data::dataAccess;
using namespace smp::data::entities;

using json = nlohmann::json;


#define LOGGING "Start logging task = %d\n"

// Methode that loads the progam data
bool loadConfiguration();

// The callback Methode for the Curl library
static size_t getApiData(void* contents, size_t size, size_t nmemb, void* userp);

int main()
{
	try
	{

	
	// Todo : replace it in logging file
	syslog(LOG_INFO, "SmpHttpClient service started ...");

	//syslog(LOG_INFO, LOGGING, "Inside the SMP Loop");

	// TODO : All this const will be replaced by params
	const string jsonSMPIdsID = "IDs";
	const string jsonSMPInformationID = "Informations";
	// Certificate path
	const string SSLCertificate = "/usr/local/share/pxmc3000/certificates/Eaton_root_ca_2.pem";
	// Refresh Time
	const int refreshTime = 2;
	// SMP IP adress
	const string stringSmpBasicUri = "https://10.106.88.181/";
	// TO by encrypted in param file
	const string username = "security";
	const string password = "Security8*";
	// Authorization header key
	const string autorizationHeader = "Authorization: Basic " + cppcodec::base64_rfc4648::encode(username + ":" + password);
	//SMP entity
	//smpDevice smpDeviceObject;
	// SMP Configuration Database path
	const char* configurationDatabaseFullPath = "/usr/local/share/pxmc3000/database/SMPConfiguration.db";
	//const char* getSMPDeviceIDUri = "api/dashboard/v1/name-plate-informations/";
	const string getSMPDeviceIDUri = "api/dashboard/v1/name-plate-informations/";
	const int loopwaitingTimeMilliseconds = 60000;

	// Http request Header Autorization value
	string authorizationHeaderValue;
	// Sqlite3DataAccess to manipulate all the data with database layer 
	dataAccess::sqlite3DataAccess smpSqlite3DataAccess(configurationDatabaseFullPath);
	// List of SMP devices returned by the API
	list<smpDevice> smpDeviceList = {};

	// Curl HTTP(s) Client declaration & initialization
	CURL* curlHandle = curl_easy_init();
	struct curl_slist* headers = NULL;
	CURLcode curlCodeResult;

	// Variables that will handle the APi reponse ID & Details
	string smpDeviceID;
	json jsonArraySMPIds;
	// Variable that will handle the APi responses
	string  responseJsonListIds;
	string reponseJsonSmpDeviceInformation;
	// Setup the get request Authorization
	headers = curl_slist_append(headers, autorizationHeader.c_str());
	curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers);

	// Ignore the SSL certification validation when it's not valid
	curl_easy_setopt(curlHandle, CURLOPT_SSL_VERIFYPEER, 0L);
	// The following line can be used to validate the certeficate
	//curl_easy_setopt(curl, CURLOPT_CAINFO, "/Eaton/certificates/10.106.88.181.pem");

	// Prepare the 
	curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, getApiData);

	// Variables to support the Time mesurement & loop time
	chrono::_V2::steady_clock::time_point getSmpDeviceInformationStart;
	chrono::milliseconds getSmpDeviceInformationDuration;
	while (true)
	{
		try
		{
			getSmpDeviceInformationStart = std::chrono::steady_clock::now();
			//sleep(refreshTime);
			//syslog(LOG_INFO, LOGGING, "Inside the SMP Loop");

			//  Step 1 : get the SMP device Ids dynamically from json
			if (curlHandle) {
				// Set the URL
				curl_easy_setopt(curlHandle, CURLOPT_URL, string(stringSmpBasicUri + getSMPDeviceIDUri).c_str());
				curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseJsonListIds);


				/* Perform the request, res will get the return code */
				curlCodeResult = curl_easy_perform(curlHandle);

				if (curlCodeResult != CURLE_OK)
				{
					// TODO : To be logged with logging mechanism
					syslog(LOG_ERR, "Error calling the SMP Api to get the Device ID list.");
					throw;
				}

				jsonArraySMPIds = json::parse(responseJsonListIds).at(jsonSMPIdsID);

				// Extract the SMP Ids list from the returned JSON
				// Loop throw each identifier and get its data
				for (auto jsonArraySMPId = jsonArraySMPIds.begin(); jsonArraySMPId != jsonArraySMPIds.end(); jsonArraySMPId++)
				{
					// Prepare the ID and remove the double quotes
					smpDeviceID = jsonArraySMPId.value().dump();
					smpDeviceID.erase(0, 1);
					smpDeviceID.erase(smpDeviceID.length() - 1);

					// Build the URI dynamically to get the Device information details based on the ID obtained dynamically
					curl_easy_setopt(curlHandle, CURLOPT_URL, string(stringSmpBasicUri + getSMPDeviceIDUri + smpDeviceID).c_str());
					curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &reponseJsonSmpDeviceInformation);

					curlCodeResult = curl_easy_perform(curlHandle);

					if (curlCodeResult != CURLE_OK)
					{
						// TODO : To be logged with logging mechanism
						syslog(LOG_ERR, "Error calling the SMP Api to get the Device information details.");
						throw;
					}
					json smpDeviceInformationDetails = json::parse(reponseJsonSmpDeviceInformation).at(jsonSMPInformationID);

					smpDeviceList.emplace_back(smpDevice{
						smpDeviceInformationDetails.at("ID").dump(),
						smpDeviceInformationDetails.at("Hardware").at("Model").dump(),
						smpDeviceInformationDetails.at("Hardware").at("SerialNumber").dump(),
						smpDeviceInformationDetails.at("Firmware").at("BootstrapVersion").dump(),
						smpDeviceInformationDetails.at("Firmware").at("OsVersion").dump(),
						smpDeviceInformationDetails.at("Firmware").at("ApplicationVersion").dump(),
						smpDeviceInformationDetails.at("Settings").at("Name").dump(),
						smpDeviceInformationDetails.at("Settings").at("Description").dump(),
						smpDeviceInformationDetails.at("Settings").at("Company").dump(),
						smpDeviceInformationDetails.at("Settings").at("Region").dump(),
						smpDeviceInformationDetails.at("Settings").at("Substation").dump(),
						smpDeviceInformationDetails.at("Settings").at("Filename").dump(),
						smpDeviceInformationDetails.at("Settings").at("FileDate").dump(),
						smpDeviceInformationDetails.at("Settings").at("FileCRC")
						});
				}

				// Store the data in the DataBase ( Sqlite at the moment of writing this comment )
				try
				{
					// Initialize the Database
					smpSqlite3DataAccess.initializeSmpDeviceBatabase();
					// Save the data
					smpSqlite3DataAccess.upsertSmpDevice(smpDeviceList.back());
				}
				catch (const exception ex)
				{
					// Todo : write to log file
					cerr << "Error saving smpDevice data: " << ex.what() << endl;
				}
			}

			// Store the data in the DataBase ( Sqlite at the moment of writing this comment )
			try
			{
				// Initialize the Database
				smpSqlite3DataAccess.initializeSmpDeviceBatabase();
				// Save the data
				smpSqlite3DataAccess.upsertSmpDevice(smpDeviceList.back());
			}
			catch (const exception ex)
			{
				// Todo : write to log file
				cerr << "Error saving smpDevice data: " << ex.what() << endl;
			}
		}
		catch (json::exception ex)
		{
			// Todo : write to log file
			syslog(LOG_ERR, "SmpHttpClient : Error calling the SMP API : ");
			syslog(LOG_ERR, ex.what());
		}

		getSmpDeviceInformationDuration = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - getSmpDeviceInformationStart);
		syslog(LOG_INFO,string("Smp device information refresh completed, duration : ").append(to_string(getSmpDeviceInformationDuration.count()).c_str()).append(" milliseconds").c_str());
		if (getSmpDeviceInformationDuration.count() < loopwaitingTimeMilliseconds)
		{
			this_thread::sleep_for(chrono::milliseconds(loopwaitingTimeMilliseconds - getSmpDeviceInformationDuration.count()));
		}

		// Clean the variables;
		responseJsonListIds.clear();
		smpDeviceList.clear();
		smpDeviceID.clear();
		jsonArraySMPIds.clear();
		responseJsonListIds.clear();
		reponseJsonSmpDeviceInformation.clear();
	}

	curl_slist_free_all(headers);

	return 0;
	}
	catch (const std::exception& ex)
	{
		cout << "SmpDataAgent exception, details : ";
		cout << ex.what();
	}
}

// Implementation section
// Todo conplete the dynamic program configuration data load
bool loadConfiguration() {
	ifstream configurationFile(CONFIG_FILE_PATH);
	if (!configurationFile.is_open())
	{
		cerr << "Fatal error, configuration file missing." << endl;
		return false;
	}
	return true;
}


static size_t getApiData(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}