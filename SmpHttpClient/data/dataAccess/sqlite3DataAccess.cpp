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

			char* messageError;
			exit = sqlite3_exec(database, sqlCreateSmpdeviceQuery.c_str(), NULL, 0, &messageError);
			if (exit != SQLITE_OK)
			{
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
		catch (const exception&)
		{
			sqlite3_close(database);
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
			"VALUES(\"" + string(smpDeviceInformation.id.begin(), smpDeviceInformation.id.end()) +
			"\",\"" + string(smpDeviceInformation.hardware.model.begin(), smpDeviceInformation.hardware.model.end()) +
			"\",\"" + string(smpDeviceInformation.hardware.serialNumber.begin(), smpDeviceInformation.hardware.serialNumber.end()) +
			"\",\"" + string(smpDeviceInformation.firmware.bootstrapVersion.begin(), smpDeviceInformation.firmware.bootstrapVersion.end()) +
			"\",\"" + string(smpDeviceInformation.firmware.osVersion.begin(), smpDeviceInformation.firmware.osVersion.end()) +
			"\",\"" + string(smpDeviceInformation.firmware.applicationVersion.begin(), smpDeviceInformation.firmware.applicationVersion.end()) +
			"\",\"" + string(smpDeviceInformation.settings.name.begin(), smpDeviceInformation.settings.name.end()) +
			"\",\"" + string(smpDeviceInformation.settings.description.begin(), smpDeviceInformation.settings.description.end()) +
			"\",\"" + string(smpDeviceInformation.settings.company.begin(), smpDeviceInformation.settings.company.end()) +
			"\",\"" + string(smpDeviceInformation.settings.Region.begin(), smpDeviceInformation.settings.Region.end()) +
			"\",\"" + string(smpDeviceInformation.settings.substation.begin(), smpDeviceInformation.settings.substation.end()) +
			"\",\"" + string(smpDeviceInformation.settings.fileName.begin(), smpDeviceInformation.settings.fileName.end()) +
			"\",\"" + string(smpDeviceInformation.settings.fileDate.begin(), smpDeviceInformation.settings.fileDate.end()) +
			"\"," + to_string(smpDeviceInformation.settings.fileCRC) +
			") ON CONFLICT([ID]) DO UPDATE SET"
			"[Hardware.Model]				= excluded.[Hardware.Model],"
			"[Hardware.SerialNumber]		= excluded.[Hardware.SerialNumber],"
			"[Firmware.BootstrapVersion]	= excluded.[Firmware.BootstrapVersion],"
			"[Firmware.OsVersion]			= excluded.[Firmware.OsVersion],"
			"[Firmware.ApplicationVersion]	= excluded.[Hardware.Model],"
			"[Settings.Name]				= excluded.[Settings.Name],"
			"[Settings.Description]			= excluded.[Settings.Description],"
			"[Settings.Company]				= excluded.[Settings.Company],"
			"[Settings.Region]				= excluded.[Settings.Region],"
			"[Settings.Substation]			= excluded.[Settings.Substation],"
			"[Settings.Filename]			= excluded.[Settings.Filename],"
			"[Settings.FileDate]			= excluded.[Settings.FileDate],"
			"[Settings.FileCRC]				= excluded.[Settings.FileCRC];";

		try
		{
			int exit = 0;
			exit = sqlite3_open(configurationDatabaseFullPath, &database);

			char* messageError;
			exit = sqlite3_exec(database, sqlQueryUpsertSmpDeviceInformation.c_str(), NULL, 0, &messageError);
			sqlite3_close(database);

		}
		catch (const std::exception&)
		{
			sqlite3_close(database);
			throw;
		}
		return 0;
	}
}