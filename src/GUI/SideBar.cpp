#include <vector>
#include <string>
#include "Imgui.hpp"
#include "imgui.h"

void Jif::GUI::Imgui::DrawSideBar()
{
	static const std::vector<std::pair<ActivePanel, std::string>> panels = {
		{ ActivePanel::INJECT, "  Inject" },
		{ ActivePanel::SETTINGS, "  Settings" }
	};

	const auto &style = ImGui::GetStyle();
	const ImVec4 &btnColor = style.Colors[ImGuiCol_Button];
	const ImVec4 &bgColor = style.Colors[ImGuiCol_WindowBg];
	const ImVec4 &textColor = style.Colors[ImGuiCol_Text];

	ImVec4 sideBarBg = ImVec4(bgColor.x * 0.7f, bgColor.y * 0.7f, bgColor.z * 0.7f, 1.0f);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, sideBarBg);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 12.0f));

	ImGui::Begin("##sidebar", nullptr,
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::SetWindowSize(ImVec2(sideBarWidth, ImGui::GetIO().DisplaySize.y));
	ImGui::SetWindowPos(ImVec2(0, 0));

	ImGui::TextColored(btnColor, "JIF");
	ImGui::SameLine();
	ImGui::TextColored(textColor, "INJECTOR");

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	for (const auto &panel : panels)
	{
		bool isActive = (mActivePanel == panel.first);

		if (isActive)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, btnColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, btnColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, btnColor);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(btnColor.x, btnColor.y, btnColor.z, 0.25f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(btnColor.x, btnColor.y, btnColor.z, 0.45f));
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(textColor.x * 0.8f, textColor.y * 0.8f, textColor.z * 0.8f, 1.0f));
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.1f, 0.5f));

		if (ImGui::Button(panel.second.c_str(), ImVec2(-1.0f, 28.0f)))
		{
			mActivePanel = panel.first;
		}

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(4);
		ImGui::Spacing();
	}

	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
