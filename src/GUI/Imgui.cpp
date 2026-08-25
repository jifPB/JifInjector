#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include "System.hpp"
#include "Imgui.hpp"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

namespace Jif::GUI
{
	Imgui::Imgui()
	{
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
		io.ConfigDebugHighlightIdConflicts = false;

		auto &style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.ChildRounding = 5.0f;
		style.FrameRounding = 4.0f;
		style.PopupRounding = 5.0f;
		style.ScrollbarRounding = 4.0f;
		style.GrabRounding = 4.0f;
		style.TabRounding = 4.0f;
		style.WindowBorderSize = 0.0f;
		style.ChildBorderSize = 1.0f;
		style.FrameBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.WindowPadding = ImVec2(12.0f, 10.0f);
		style.FramePadding = ImVec2(8.0f, 4.0f);
		style.ItemSpacing = ImVec2(8.0f, 6.0f);
		style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);

		GetProcessesNames();
		ApplyThemePreset();
	}

	void Imgui::InitWin32AndDX11(
		const HWND &window, Microsoft::WRL::ComPtr<ID3D11Device> device,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext
	)
	{
		if (ImGui_ImplWin32_Init(window) == false)
		{
			throw std::runtime_error("Failed to initialize ImGui Win32");
		}
		if (ImGui_ImplDX11_Init(device.Get(), deviceContext.Get()) == false)
		{
			throw std::runtime_error("Failed to initialize ImGui DX11");
		}
	}

	Imgui::~Imgui()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void Imgui::Render()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void Imgui::Draw()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		DrawSideBar();
		MaximizeMainWindow();
		ImGui::Begin(
			"JifInjector", nullptr,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus
		);
		DrawPanels();
		ImGui::End();
	}

	void Imgui::DrawPanels()
	{
		static const std::unordered_map<ActivePanel, std::function<void()>> mPanelsDrawers = {
			{ActivePanel::INJECT, std::bind(&Imgui::DrawInjectPanel, this)},
			{ActivePanel::SETTINGS, std::bind(&Imgui::DrawSettingsPanel, this)}
		};

		auto it = mPanelsDrawers.find(mActivePanel);
		if (it != mPanelsDrawers.end())
		{
			it->second();
		}
	}

	void Imgui::MaximizeMainWindow()
	{
		ImGui::SetNextWindowSize(
			ImVec2(ImGui::GetIO().DisplaySize.x - sideBarWidth, ImGui::GetIO().DisplaySize.y)
		);
		ImGui::SetNextWindowPos(mainWindowPos);
	}

	void Imgui::GetProcessesNames()
	{
		mProcessesNames = Jif::System::GetRunningProcessesNames();
		std::sort(mProcessesNames.begin(), mProcessesNames.end());
		mProcessesNames.erase(
			std::unique(mProcessesNames.begin(), mProcessesNames.end()),
			mProcessesNames.end()
		);
	}

	void Imgui::ApplyThemePreset()
	{
		auto &imguiStyle = ImGui::GetStyle();
		const auto &jifStyle = Settings::StyleSettings::GetInstance();
		const auto &bg = jifStyle.GetBackgroundColor();
		const auto &text = jifStyle.GetTextColor();
		const auto &border = jifStyle.GetBorderColor();
		const auto &btn = jifStyle.GetButtonColor();

		imguiStyle.Colors[ImGuiCol_WindowBg] = ImVec4(bg.x, bg.y, bg.z, bg.w);
		imguiStyle.Colors[ImGuiCol_ChildBg] = ImVec4(bg.x * 1.15f, bg.y * 1.15f, bg.z * 1.15f, 0.65f);
		imguiStyle.Colors[ImGuiCol_PopupBg] = ImVec4(bg.x * 1.25f, bg.y * 1.25f, bg.z * 1.25f, 0.98f);
		imguiStyle.Colors[ImGuiCol_Text] = ImVec4(text.x, text.y, text.z, text.w);
		imguiStyle.Colors[ImGuiCol_TextDisabled] = ImVec4(text.x * 0.55f, text.y * 0.55f, text.z * 0.55f, 1.0f);
		imguiStyle.Colors[ImGuiCol_Border] = ImVec4(border.x, border.y, border.z, border.w);
		imguiStyle.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

		imguiStyle.Colors[ImGuiCol_FrameBg] = ImVec4(bg.x * 1.5f + 0.03f, bg.y * 1.5f + 0.03f, bg.z * 1.5f + 0.03f, 0.9f);
		imguiStyle.Colors[ImGuiCol_FrameBgHovered] = ImVec4(bg.x * 2.0f + 0.05f, bg.y * 2.0f + 0.05f, bg.z * 2.0f + 0.05f, 1.0f);
		imguiStyle.Colors[ImGuiCol_FrameBgActive] = ImVec4(btn.x * 0.5f, btn.y * 0.5f, btn.z * 0.5f, 0.7f);

		imguiStyle.Colors[ImGuiCol_Button] = ImVec4(btn.x, btn.y, btn.z, btn.w);
		imguiStyle.Colors[ImGuiCol_ButtonHovered] = ImVec4((std::min)(1.0f, btn.x * 1.2f + 0.05f), (std::min)(1.0f, btn.y * 1.2f + 0.05f), (std::min)(1.0f, btn.z * 1.2f + 0.05f), 1.0f);
		imguiStyle.Colors[ImGuiCol_ButtonActive] = ImVec4(btn.x * 0.85f, btn.y * 0.85f, btn.z * 0.85f, 1.0f);

		imguiStyle.Colors[ImGuiCol_Header] = ImVec4(btn.x * 0.4f, btn.y * 0.4f, btn.z * 0.4f, 0.6f);
		imguiStyle.Colors[ImGuiCol_HeaderHovered] = ImVec4(btn.x * 0.6f, btn.y * 0.6f, btn.z * 0.6f, 0.8f);
		imguiStyle.Colors[ImGuiCol_HeaderActive] = ImVec4(btn.x, btn.y, btn.z, 0.9f);

		imguiStyle.Colors[ImGuiCol_CheckMark] = ImVec4(btn.x * 1.3f, btn.y * 1.3f, btn.z * 1.3f, 1.0f);
		imguiStyle.Colors[ImGuiCol_SliderGrab] = ImVec4(btn.x, btn.y, btn.z, 1.0f);
		imguiStyle.Colors[ImGuiCol_SliderGrabActive] = ImVec4(btn.x * 1.2f, btn.y * 1.2f, btn.z * 1.2f, 1.0f);
		imguiStyle.Colors[ImGuiCol_ScrollbarBg] = ImVec4(bg.x * 0.8f, bg.y * 0.8f, bg.z * 0.8f, 0.5f);
		imguiStyle.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(bg.x * 2.0f, bg.y * 2.0f, bg.z * 2.0f, 0.7f);
		imguiStyle.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(btn.x * 0.7f, btn.y * 0.7f, btn.z * 0.7f, 0.8f);
		imguiStyle.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(btn.x, btn.y, btn.z, 1.0f);
		imguiStyle.Colors[ImGuiCol_Separator] = ImVec4(border.x, border.y, border.z, 0.4f);
	}
}
