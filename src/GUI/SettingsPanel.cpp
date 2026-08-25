#include <string>
#include <vector>
#include <functional>
#include "imgui.h"
#include "Imgui.hpp"
#include "JifSettings.hpp"
#include "StyleSettings.hpp"
#include "ThemePresets.hpp"

namespace Jif::GUI
{
	struct ThemeOption
	{
		const char *name;
		std::function<void()> apply;
	};

	static const std::vector<ThemeOption> themeList = {
		{"Default (Slate Indigo)", Themes::SetDefaultColors},
		{"Midnight (Neon Blue)", Themes::SetMidnightColors},
		{"Cyberpunk (Teal & Pink)", Themes::SetCyberpunkColors},
		{"Emerald (Forest Green)", Themes::SetEmeraldColors},
		{"Purple (Violet)", Themes::SetPurpleColors},
		{"Ocean (Deep Blue)", Themes::SetOceanColors},
		{"Black & White", Themes::SetBlackAndWhiteColors}
	};

	static int currentThemeIndex = 0;

	static void customTheme()
	{
		constexpr std::string_view backgroundLabel = "Background Color";
		constexpr std::string_view textLabel = "Text Color";
		constexpr std::string_view borderLabel = "Border Color";
		constexpr std::string_view buttonLabel = "Accent / Button Color";
		auto &style = Settings::StyleSettings::GetInstance();

		Imgui::CustomColorPicker(
			backgroundLabel,
			[&style]() -> const Vector4 & { return style.GetBackgroundColor(); },
			[&style](const Vector4 &color) { style.SetBackgroundColor(color); },
			ImGuiCol_WindowBg
		);
		Imgui::CustomColorPicker(
			textLabel, [&style]() -> const Vector4 & { return style.GetTextColor(); },
			[&style](const Vector4 &color) { style.SetTextColor(color); },
			ImGuiCol_Text
		);
		Imgui::CustomColorPicker(
			borderLabel,
			[&style]() -> const Vector4 & { return style.GetBorderColor(); },
			[&style](const Vector4 &color) { style.SetBorderColor(color); },
			ImGuiCol_Border
		);
		Imgui::CustomColorPicker(
			buttonLabel,
			[&style]() -> const Vector4 & { return style.GetButtonColor(); },
			[&style](const Vector4 &color) { style.SetButtonColor(color); },
			ImGuiCol_Button
		);
	}

	void Imgui::DrawSettingsPanel()
	{
		ImGui::Text("Theme & Customization");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("Preset Themes");
		ImGui::SetNextItemWidth(-1.0f);
		if (ImGui::BeginCombo("##themeCombo", themeList[currentThemeIndex].name))
		{
			for (size_t i = 0; i < themeList.size(); i++)
			{
				bool isSelected = (currentThemeIndex == static_cast<int>(i));
				if (ImGui::Selectable(themeList[i].name, isSelected))
				{
					currentThemeIndex = static_cast<int>(i);
					themeList[i].apply();
					ApplyThemePreset();
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("Custom Colors");
		ImGui::Spacing();
		customTheme();
	}
}
