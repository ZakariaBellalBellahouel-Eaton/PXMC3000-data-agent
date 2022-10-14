/***
 * Copyright (C) Eaton. All rights reserved.
 * Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Struct that represents the SMP device firmware
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/
#ifndef SMP_DATA_FIRMWARE_H
#define SMP_DATA_FIRMWARE_H

#include<string>


namespace smp::data::entities {
	struct firmware {
		std::string bootstrapVersion;
		std::string osVersion;
		std::string applicationVersion;
	};
}

#endif