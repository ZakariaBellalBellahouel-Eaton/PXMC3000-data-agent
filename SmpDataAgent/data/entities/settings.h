/***
 * Copyright (C) Eaton. All rights reserved.
 * Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Struct that represents the SMP device settings.
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/
#ifndef SMP_DATA_SETTINGS_H
#define SMP_DATA_SETTINGS_H

#include<string>

namespace smp::data::entities {
	struct settings {
		std::string name;
		std::string description;
		std::string company;
		std::string Region;
		std::string substation;
		std::string fileName;
		std::string fileDate;
		int fileCRC;
	};
}

#endif