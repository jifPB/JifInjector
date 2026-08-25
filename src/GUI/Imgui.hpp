#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include "ModInfos.hpp"
#include "MonoModule.hpp"
#include "imgui.h"
#include "StyleSettings.hpp"

namespace Jif
{
	namespace GUI
	{
		class Imgui
		{
			static constexpr float sideBarWidth = 115.0f;
			static constexpr ImVec2 mainWindowPos = ImVec2(sideBarWidth, 0.0f);

		public:
			Imgui();
			~Imgui();

			void InitWin32AndDX11(
				const HWND &window, Microsoft::WRL::ComPtr<ID3D11Device> device,
				Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext
			);
			void Draw();
			void Render();

			static void CustomColorPicker(
				const std::string_view label, std::function<Vector4()> getter,
				std::function<void(const Vector4 &)> setter, ImGuiCol_ colorIndex
			);

		private:
			enum class ActivePanel : uint8_t
			{
				INJECT,
				SETTINGS
			};

			void DrawSideBar();
			void DrawPanels();
			void MaximizeMainWindow();

			void DrawInjectPanel();
			void DrawProcessesBox();
			void DrawDllBox();
			void DrawInjectInputs();
			void DrawInjectButton();
			void GetProcessesNames();
			void OpenDllFileDialog();

			void DrawSettingsPanel();

			void ApplyThemePreset();

			Injector::ModInfos mModInfos;
			std::size_t mSelectedProcessIndex = 0;
			std::vector<std::string> mProcessesNames;
			ActivePanel mActivePanel = ActivePanel::INJECT;
			std::string mStatusMessage;
			bool mStatusSuccess = false;
		};
	}
}
