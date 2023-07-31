#include <windows.h>
#include <iostream>
#include <sstream>

namespace deviceIDGenerator
{
	class deviceIDGenerator
	{
		public:

		bool GenerateMonitorID(const std::string& name, const RECT& workArea);
	};
}


