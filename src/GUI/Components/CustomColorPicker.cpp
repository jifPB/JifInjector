#include "Imgui.hpp"
#include "imgui.h"

namespace Jif
{
	namespace GUI
	{
		static bool colorLabelClickable(const std::string_view label, const ImVec4 &color)
		{
			bool isClicked = false;

			if (ImGui::ColorButton("##ColorBtn", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip))
			{
				isClicked = true;
			}
			ImGui::SameLine();
			ImGui::Text("%s", label.data());
			if (ImGui::IsItemClicked())
			{
				isClicked = true;
			}
			return isClicked;
		}

		static bool drawPopup(ImVec4 &color)
		{
			if (ImGui::BeginPopup("##ColorPopup"))
			{
				ImGui::ColorPicker4(
					"##Picker", (float *)&color,
					ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview
				);
				return true;
			}
			return false;
		}

		void Imgui::CustomColorPicker(
			const std::string_view label, std::function<Vector4()> getter,
			std::function<void(const Vector4 &)> setter, ImGuiCol_ colorIndex
		)
		{
			ImGui::PushID(label.data());
			const auto &settingColor = getter();
			ImVec4 color{settingColor.x, settingColor.y, settingColor.z, settingColor.w};
			bool isClicked = colorLabelClickable(label, color);

			if (isClicked)
			{
				ImGui::OpenPopup("##ColorPopup");
			}
			if (drawPopup(color))
			{
				ImGui::GetStyle().Colors[colorIndex] =
					ImVec4(color.x, color.y, color.z, color.w);
				setter({color.x, color.y, color.z, color.w});
				ImGui::EndPopup();
			}
			ImGui::PopID();
		}
	}
}
