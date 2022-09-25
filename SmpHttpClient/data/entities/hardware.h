/***
 * Copyright (C) Eaton. All rights reserved.
 * Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Struct that represents the SMP device hardware information
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/
#ifndef SMP_DATA_HARDWARE_H
#define SMP_DATA_HARDWARE_H

#include<string>

namespace smp::data::entities {
	struct hardware {
		std::string model;
		std::string serialNumber;
	};
}

#endif