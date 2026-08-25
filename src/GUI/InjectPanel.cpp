#include <windows.h>
#include <commdlg.h>
#include <filesystem>
#include "imgui.h"
#include "Imgui.hpp"
#include "System.hpp"
#include "ModsManager.hpp"

namespace Jif::GUI
{
	void Imgui::OpenDllFileDialog()
	{
		OPENFILENAMEA ofn;
		char filePath[MAX_PATH] = {0};
		char currentDir[MAX_PATH] = {0};
		GetCurrentDirectoryA(MAX_PATH, currentDir);

		if (!mModInfos.modPath.empty())
		{
			strcpy_s(filePath, sizeof(filePath), mModInfos.modPath.c_str());
		}

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFilter = "Dynamic Link Library (*.dll)\0*.dll\0All Files (*.*)\0*.*\0";
		ofn.lpstrFile = filePath;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = "Select DLL to Inject";
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

		if (GetOpenFileNameA(&ofn))
		{
			SetCurrentDirectoryA(currentDir);
			mModInfos.modPath = ofn.lpstrFile;

			if (mModInfos.modNamespace.empty()) mModInfos.modNamespace = "Main";
			if (mModInfos.modClass.empty()) mModInfos.modClass = "Loader";
			if (mModInfos.modInitMethod.empty()) mModInfos.modInitMethod = "Load";
			mStatusMessage.clear();
		}
	}

	void Imgui::DrawProcessesBox()
	{
		ImGui::Text("Target Process");

		const float refreshBtnWidth = 65.0f;
		const float comboWidth = ImGui::GetContentRegionAvail().x - refreshBtnWidth - 6.0f;

		ImGui::SetNextItemWidth(comboWidth);
		const char *previewValue = mProcessesNames.empty() ? "No processes running" : mProcessesNames[mSelectedProcessIndex].c_str();

		if (ImGui::BeginCombo("##processCombo", previewValue))
		{
			for (size_t i = 0; i < mProcessesNames.size(); i++)
			{
				bool isSelected = (mSelectedProcessIndex == i);
				if (ImGui::Selectable(mProcessesNames[i].c_str(), isSelected))
				{
					mSelectedProcessIndex = i;
					mStatusMessage.clear();
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::SameLine();
		if (ImGui::Button("Refresh", ImVec2(refreshBtnWidth, 0)))
		{
			GetProcessesNames();
			if (mSelectedProcessIndex >= mProcessesNames.size())
			{
				mSelectedProcessIndex = 0;
			}
		}
	}

	void Imgui::DrawDllBox()
	{
		ImGui::Text("DLL File");

		const auto &style = ImGui::GetStyle();
		const ImVec4 &btnColor = style.Colors[ImGuiCol_Button];
		const ImVec4 &frameBg = style.Colors[ImGuiCol_FrameBg];

		std::string buttonText;
		if (mModInfos.modPath.empty())
		{
			buttonText = "[ Select DLL ]  Click to browse files...";
		}
		else
		{
			buttonText = "[DLL]  " + std::filesystem::path(mModInfos.modPath).filename().string();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, frameBg);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(frameBg.x * 1.3f + 0.05f, frameBg.y * 1.3f + 0.05f, frameBg.z * 1.3f + 0.05f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, btnColor);
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.03f, 0.5f));

		if (ImGui::Button(buttonText.c_str(), ImVec2(-1.0f, 28.0f)))
		{
			OpenDllFileDialog();
		}

		ImGui::PopStyleVar();
		ImGui::PopStyleColor(3);

		if (!mModInfos.modPath.empty())
		{
			ImGui::TextDisabled("%s", mModInfos.modPath.c_str());
		}
	}

	void Imgui::DrawInjectInputs()
	{

		char namespaceBuffer[256] = {0};
		char classNameBuffer[256] = {0};
		char loadMethodNameBuffer[256] = {0};

		strcpy_s(namespaceBuffer, sizeof(namespaceBuffer), mModInfos.modNamespace.c_str());
		strcpy_s(classNameBuffer, sizeof(classNameBuffer), mModInfos.modClass.c_str());
		strcpy_s(loadMethodNameBuffer, sizeof(loadMethodNameBuffer), mModInfos.modInitMethod.c_str());

		float fieldWidth = (ImGui::GetContentRegionAvail().x - 12.0f) / 3.0f;

		ImGui::BeginGroup();
		ImGui::TextDisabled("Namespace");
		ImGui::SetNextItemWidth(fieldWidth);
		if (ImGui::InputText("##namespace", namespaceBuffer, IM_ARRAYSIZE(namespaceBuffer)))
		{
			mModInfos.modNamespace = namespaceBuffer;
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::TextDisabled("Class");
		ImGui::SetNextItemWidth(fieldWidth);
		if (ImGui::InputText("##class", classNameBuffer, IM_ARRAYSIZE(classNameBuffer)))
		{
			mModInfos.modClass = classNameBuffer;
		}
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::TextDisabled("Load Method");
		ImGui::SetNextItemWidth(fieldWidth);
		if (ImGui::InputText("##loadMethod", loadMethodNameBuffer, IM_ARRAYSIZE(loadMethodNameBuffer)))
		{
			mModInfos.modInitMethod = loadMethodNameBuffer;
		}
		ImGui::EndGroup();
	}

	void Imgui::DrawInjectButton()
	{
		ImGui::Spacing();

		if (!mStatusMessage.empty())
		{
			if (mStatusSuccess)
			{
				ImGui::TextColored(ImVec4(0.2f, 0.9f, 0.3f, 1.0f), "[OK] %s", mStatusMessage.c_str());
			}
			else
			{
				ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "[ERR] %s", mStatusMessage.c_str());
			}
			ImGui::Spacing();
		}

		if (ImGui::Button("Inject DLL", ImVec2(-1.0f, 32.0f)))
		{
			if (mProcessesNames.empty() || mSelectedProcessIndex >= mProcessesNames.size())
			{
				mStatusMessage = "Please select a target process first.";
				mStatusSuccess = false;
				return;
			}

			if (mModInfos.modPath.empty())
			{
				mStatusMessage = "Please select a DLL file first.";
				mStatusSuccess = false;
				OpenDllFileDialog();
				return;
			}

			DWORD fileAttr = GetFileAttributesA(mModInfos.modPath.c_str());
			if (fileAttr == INVALID_FILE_ATTRIBUTES || (fileAttr & FILE_ATTRIBUTE_DIRECTORY))
			{
				mStatusMessage = "The selected DLL file does not exist on disk.";
				mStatusSuccess = false;
				return;
			}

			if (mModInfos.modNamespace.empty() || mModInfos.modClass.empty() || mModInfos.modInitMethod.empty())
			{
				mStatusMessage = "Namespace, Class, and Load Method cannot be empty.";
				mStatusSuccess = false;
				return;
			}

			try
			{
				mModInfos.targetedProcessName = mProcessesNames[mSelectedProcessIndex];
				Jif::Injector::ModsManager &modsManager = Jif::Injector::ModsManager::getInstance();
				modsManager.LoadMod(mModInfos);
				mStatusMessage = "Successfully injected into " + mModInfos.targetedProcessName;
				mStatusSuccess = true;
			}
			catch (const std::exception &e)
			{
				mStatusMessage = e.what();
				mStatusSuccess = false;
			}
		}
	}

	void Imgui::DrawInjectPanel()
	{
		DrawProcessesBox();
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		DrawDllBox();
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		DrawInjectInputs();
		ImGui::Spacing();
		ImGui::Separator();

		DrawInjectButton();
	}
}
