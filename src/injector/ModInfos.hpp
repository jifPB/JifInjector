#pragma once

#include <string>

namespace Jif::Injector
{
	struct ModInfos
	{
		std::string modPath;
		std::string modNamespace;
		std::string modClass;
		std::string modInitMethod;
		std::string targetedProcessName;

		bool operator==(const ModInfos &other) const
		{
			if (modPath != other.modPath ||
				modNamespace != other.modNamespace ||
				modClass != other.modClass) {
				return false;
			}
			return true;
		}
	};
}
