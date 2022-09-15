/***
 * Copyright (C) Eaton. All rights reserved.
 * Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Struct that represents the SMP device
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/
#ifndef SMP_DATA_SMPDEVICE_H
#define SMP_DATA_SMPDEVICE_H

#include "firmware.h"
#include "hardware.h"
#include "settings.h"

namespace smp::data::entities {
	struct smpDevice {
		utility::string_t id;
		hardware hardware;
		firmware firmware;
		settings settings;
		// Constructor to allow the initialization of the structure when passing it as param
		smpDevice(utility::string_t id,
			utility::string_t hardwareModel,
			utility::string_t hardwareSerialNumber,
			utility::string_t firmwareBootstrapVersion,
			utility::string_t firmwareOsVersion,
			utility::string_t firmwareApplicationVersion,
			utility::string_t settingsName,
			utility::string_t settingsDescription,
			utility::string_t idsettingsCompany,
			utility::string_t settingsRegion,
			utility::string_t settingsSubstation,
			utility::string_t settingsFileName,
			utility::string_t settingsFileDate,
			int settingsFileCRC
		) {
			id = id;
			hardware.model = hardwareModel;
			hardware.serialNumber = hardwareSerialNumber;
			firmware.bootstrapVersion = firmwareBootstrapVersion;
			firmware.osVersion = firmwareOsVersion;
			firmware.applicationVersion = firmwareApplicationVersion;
			settings.name = settingsName;
			settings.description = settingsDescription;
			settings.company = idsettingsCompany;
			settings.Region = settingsRegion;
			settings.substation = settingsSubstation;
			settings.fileName = settingsFileName;
			settings.fileDate = settingsFileDate;
			settings.fileCRC = settingsFileCRC;
		}
	};
}

#endif