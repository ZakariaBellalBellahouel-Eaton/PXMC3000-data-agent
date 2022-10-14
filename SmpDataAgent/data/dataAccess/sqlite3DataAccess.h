// Class that encapsulate all the data access layer for Sqlite3

#include <sqlite3.h>
#include<iostream>
#include "../entities/smpDevice.h"

#ifndef SQLLITEDATAACESS_H
#define SQLLITEDATAACESS_H

using namespace smp::data;

namespace smp::data::dataAccess
{
	class sqlite3DataAccess
	{
	public:
		sqlite3DataAccess(const char* databaseFileFullPath);
		~sqlite3DataAccess();
		int initializeSmpDeviceBatabase();
		int upsertSmpDevice(entities::smpDevice smpDeviceInformation);


	private:
		sqlite3* database;
		const char* configurationDatabaseFullPath;

	};
}
#endif
