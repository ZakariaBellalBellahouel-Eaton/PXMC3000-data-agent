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
		std::string id;
		hardware smpHardware;
		firmware smpFirmware;
		settings smpSettings;
		// Constructor to allow the initialization of the structure when passing it as param
		smpDevice(
			std::string id,
			std::string hardwareModel,
			std::string hardwareSerialNumber,
			std::string firmwareBootstrapVersion,
			std::string firmwareOsVersion,
			std::string firmwareApplicationVersion,
			std::string settingsName,
			std::string settingsDescription,
			std::string idsettingsCompany,
			std::string settingsRegion,
			std::string settingsSubstation,
			std::string settingsFileName,
			std::string settingsFileDate,
			int settingsFileCRC
		) {
			this->id = id;
			smpHardware.model = hardwareModel;
			smpHardware.serialNumber = hardwareSerialNumber;
			smpFirmware.bootstrapVersion = firmwareBootstrapVersion;
			smpFirmware.osVersion = firmwareOsVersion;
			smpFirmware.applicationVersion = firmwareApplicationVersion;
			smpSettings.name = settingsName;
			smpSettings.description = settingsDescription;
			smpSettings.company = idsettingsCompany;
			smpSettings.Region = settingsRegion;
			smpSettings.substation = settingsSubstation;
			smpSettings.fileName = settingsFileName;
			smpSettings.fileDate = settingsFileDate;
			smpSettings.fileCRC = settingsFileCRC;
		}
	};
}

#endif