#pragma once

#include "StyleSettings.hpp"

namespace Jif::Themes
{
	inline void SetDefaultColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.10f, 0.11f, 0.14f, 1.0f});
		style.SetTextColor({0.94f, 0.95f, 0.98f, 1.0f});
		style.SetBorderColor({0.24f, 0.26f, 0.34f, 1.0f});
		style.SetButtonColor({0.38f, 0.34f, 0.92f, 1.0f});
	}

	inline void SetMidnightColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.06f, 0.07f, 0.09f, 1.0f});
		style.SetTextColor({0.90f, 0.93f, 0.98f, 1.0f});
		style.SetBorderColor({0.16f, 0.20f, 0.28f, 1.0f});
		style.SetButtonColor({0.15f, 0.50f, 0.95f, 1.0f});
	}

	inline void SetCyberpunkColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.08f, 0.06f, 0.14f, 1.0f});
		style.SetTextColor({0.98f, 0.98f, 1.0f, 1.0f});
		style.SetBorderColor({0.85f, 0.15f, 0.65f, 1.0f});
		style.SetButtonColor({0.08f, 0.82f, 0.76f, 1.0f});
	}

	inline void SetEmeraldColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.07f, 0.10f, 0.08f, 1.0f});
		style.SetTextColor({0.92f, 0.97f, 0.93f, 1.0f});
		style.SetBorderColor({0.18f, 0.30f, 0.22f, 1.0f});
		style.SetButtonColor({0.16f, 0.72f, 0.42f, 1.0f});
	}

	inline void SetPurpleColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.12f, 0.09f, 0.18f, 1.0f});
		style.SetTextColor({0.95f, 0.92f, 0.98f, 1.0f});
		style.SetBorderColor({0.28f, 0.20f, 0.38f, 1.0f});
		style.SetButtonColor({0.55f, 0.25f, 0.85f, 1.0f});
	}

	inline void SetOceanColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.05f, 0.12f, 0.18f, 1.0f});
		style.SetTextColor({0.92f, 0.96f, 0.99f, 1.0f});
		style.SetBorderColor({0.18f, 0.32f, 0.45f, 1.0f});
		style.SetButtonColor({0.18f, 0.62f, 0.85f, 1.0f});
	}

	inline void SetBlackAndWhiteColors()
	{
		auto &style = Settings::StyleSettings::GetInstance();

		style.SetBackgroundColor({0.08f, 0.08f, 0.08f, 1.0f});
		style.SetTextColor({0.90f, 0.90f, 0.90f, 1.0f});
		style.SetBorderColor({0.28f, 0.28f, 0.28f, 1.0f});
		style.SetButtonColor({0.35f, 0.35f, 0.35f, 1.0f});
	}
}
