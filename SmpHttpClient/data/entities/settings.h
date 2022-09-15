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

#include <string>
#include <ctime>

namespace smp::data::entities {
	struct settings {
		utility::string_t name;
		utility::string_t description;
		utility::string_t company;
		utility::string_t Region;
		utility::string_t substation;
		utility::string_t fileName;
		utility::string_t fileDate;
		int fileCRC;
	};
}

#endif