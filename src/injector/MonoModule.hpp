#pragma once

#include <Windows.h>
#include <unordered_map>
#include <string>
#include "ModInfos.hpp"

namespace Jif
{
	namespace Injector
	{
		class MonoModule
		{
		public:
			MonoModule(HANDLE hProcess, const ModInfos &modInfos);
			~MonoModule() = default;

			bool LoadMod();

		private:
			void FindMonoFunctions();
			void FindMonoModule();

			void GetMonoDomain();
			void GetMonoAssembly();
			void GetMonoImage();
			void GetMonoClass();
			void GetMonoInitMethod();

			void MonoRuntimeInvoke(LPVOID method);

			HANDLE	_hProcess;
			HMODULE _monoModule;

			LPVOID _monoRootDomain = nullptr;
			LPVOID _monoAssembly = nullptr;
			LPVOID _monoImage = nullptr;
			LPVOID _monoClass = nullptr;
			LPVOID _monoInitMethod = nullptr;

			ModInfos _modInfos;
			std::unordered_map<std::string, LPVOID> _monoFunctions;
		};
	}
}
