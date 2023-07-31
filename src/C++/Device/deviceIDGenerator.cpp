#include "deviceIDGenerator.h"

namespace deviceIDGenerator{

	bool GenerateMonitorID(const std::string& name, const RECT& workArea)
	{
	std::stringstream ss;
	ss << name << workArea.right << workArea.bottom;
	std::string combined = ss.str();

	// Generate hash value using SHA-256 algorithm
	// Using OpenSSL library for this process

	// unsigned char hash[SHA256_DIGEST_LENGTH];

	return true;
	}
}

