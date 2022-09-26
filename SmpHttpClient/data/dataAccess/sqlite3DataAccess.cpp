#include "sqlite3DataAccess.h"
using namespace std;

namespace smp::data::dataAccess
{
	sqlite3DataAccess::sqlite3DataAccess(const char* databaseFileFullPath) {
		configurationDatabaseFullPath = databaseFileFullPath;
	}
	sqlite3DataAccess::~sqlite3DataAccess() {
	}

	int sqlite3DataAccess::initializeSmpDeviceBatabase() {
		string sqlCreateSmpdeviceQuery =
			"CREATE TABLE IF NOT EXISTS [SmpDevice]("
			"[ID]							TEXT PRIMARY KEY,"
			"[Hardware.Model]				TEXT NULL,"
			"[Hardware.SerialNumber]		TEXT NULL,"
			"[Firmware.BootstrapVersion]	TEXT NULL,"
			"[Firmware.OsVersion]			TEXT NULL,"
			"[Firmware.ApplicationVersion]	TEXT NULL,"
			"[Settings.Name]				TEXT NULL,"
			"[Settings.Description]			TEXT NULL,"
			"[Settings.Company]				TEXT NULL,"
			"[Settings.Region]				TEXT NULL,"
			"[Settings.Substation]			TEXT NULL,"
			"[Settings.Filename]			TEXT NULL,"
			"[Settings.FileDate]			TEXT NULL,"
			"[Settings.FileCRC]				TEXT NULL,"
			"[CreationDateTime]				TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
			"[ModificationDateTime]			TEXT"
			");"
			"CREATE TRIGGER IF NOT EXISTS [CreationModificationTracking_SmpDevice_Insert] "
			"AFTER UPDATE ON [SmpDevice] "
			"BEGIN "
			"UPDATE [SmpDevice] SET "
			"[ModificationDateTime] = CURRENT_TIMESTAMP "
			"WHERE [ID] = NEW.[ID];"
			"END; ";

		try
		{
			int exit = 0;
			exit = sqlite3_open(configurationDatabaseFullPath, &database);
			if (exit == SQLITE_OK)
			{
				char* messageError;
				exit = sqlite3_exec(database, sqlCreateSmpdeviceQuery.c_str(), NULL, 0, &messageError);
				if (exit != SQLITE_OK)
				{
					// Todo : write to log file
					cerr << "Error Create Table SMPDevice" << endl;
					cerr << messageError << endl;
					sqlite3_free(messageError);
				}
				else
				{
					cout << "Table SmpDevice created Successfully" << endl;
				}
				sqlite3_close_v2(database);
			}
			else
			{
				// Todo : write to log file
				cerr << "Failed to open/create database file" << endl;
			}

		}
		catch (exception ex)
		{
			sqlite3_close(database);
			cerr << ex.what();
			throw;
		}

		return 0;
	}

	int sqlite3DataAccess::upsertSmpDevice(entities::smpDevice smpDeviceInformation)
	{
		string sqlQueryUpsertSmpDeviceInformation =
			"INSERT INTO SmpDevice([ID],[Hardware.Model],[Hardware.SerialNumber],[Firmware.BootstrapVersion],"
			"[Firmware.OsVersion],[Firmware.ApplicationVersion],[Settings.Name],[Settings.Description],[Settings.Company],"
			"[Settings.Region],[Settings.Substation],[Settings.Filename],[Settings.FileDate],[Settings.FileCRC])"
			"VALUES(" + smpDeviceInformation.id +
			"," + smpDeviceInformation.smpHardware.model +
			"," + smpDeviceInformation.smpHardware.serialNumber +
			"," + smpDeviceInformation.smpFirmware.bootstrapVersion +
			"," + smpDeviceInformation.smpFirmware.osVersion +
			"," + smpDeviceInformation.smpFirmware.applicationVersion +
			"," + smpDeviceInformation.smpSettings.name +
			"," + smpDeviceInformation.smpSettings.description +
			"," + smpDeviceInformation.smpSettings.company +
			"," + smpDeviceInformation.smpSettings.Region +
			"," + smpDeviceInformation.smpSettings.substation +
			"," + smpDeviceInformation.smpSettings.fileName +
			"," + smpDeviceInformation.smpSettings.fileDate +
			"," + to_string(smpDeviceInformation.smpSettings.fileCRC) +
			") ON CONFLICT([ID]) DO UPDATE SET" +
			"[Hardware.Model]				= excluded.[Hardware.Model]," +
			"[Hardware.SerialNumber]		= excluded.[Hardware.SerialNumber]," +
			"[Firmware.BootstrapVersion]	= excluded.[Firmware.BootstrapVersion]," +
			"[Firmware.OsVersion]			= excluded.[Firmware.OsVersion]," +
			"[Firmware.ApplicationVersion]	= excluded.[Hardware.Model]," +
			"[Settings.Name]				= excluded.[Settings.Name]," +
			"[Settings.Description]			= excluded.[Settings.Description]," +
			"[Settings.Company]				= excluded.[Settings.Company]," +
			"[Settings.Region]				= excluded.[Settings.Region]," +
			"[Settings.Substation]			= excluded.[Settings.Substation]," +
			"[Settings.Filename]			= excluded.[Settings.Filename]," +
			"[Settings.FileDate]			= excluded.[Settings.FileDate]," +
			"[Settings.FileCRC]				= excluded.[Settings.FileCRC];";

		try
		{
			int exit = 0;
			exit = sqlite3_open(configurationDatabaseFullPath, &database);

			char* messageError;
			exit = sqlite3_exec(database, sqlQueryUpsertSmpDeviceInformation.c_str(), NULL, 0, &messageError);
			sqlite3_close(database);
			// Todo : write to log file
		}
		catch (const std::exception&)
		{
			// Todo : write to log file
			sqlite3_close(database);
			throw;
		}
		return 0;
	}
}