#include <Windows.h>
#include "ModsManager.hpp"
#include "System.hpp"

namespace Jif::Injector
{
    void ModsManager::LoadMod(const ModInfos &modInfos)
    {
        for (auto &loadedMod : mLoadedMods) {
            if (loadedMod.first == modInfos) {
                MessageBoxA(nullptr, "Mod already loaded", "Error", MB_OK | MB_ICONERROR);
                return;
            }
        }
        HANDLE hProcess = Jif::System::GetProcessHandleByName(modInfos.targetedProcessName);
        mLoadedMods.emplace_back(modInfos, MonoModule(hProcess, modInfos));
        mLoadedMods.back().second.LoadMod();
    }

    const std::vector<std::pair<ModInfos, MonoModule>> &ModsManager::getLoadedMods() const
    {
        return mLoadedMods;
    }
}
