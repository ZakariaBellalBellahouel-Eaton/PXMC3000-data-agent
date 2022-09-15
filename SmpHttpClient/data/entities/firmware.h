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

#include <string>
#include <cpprest/details/basic_types.h>

namespace smp::data::entities {
			struct firmware {
				utility::string_t bootstrapVersion;
				utility::string_t osVersion;
				utility::string_t applicationVersion;
			};
}

#endif