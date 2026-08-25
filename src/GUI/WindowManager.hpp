#pragma once

#include <windows.h>
#include "DirectX11.hpp"
#include "Imgui.hpp"

namespace Jif
{
	namespace GUI
	{
		class WindowManager
		{
			static constexpr LPCWSTR WindowName = L"JifInjector";
			static constexpr UINT WindowWidth = 580;
			static constexpr UINT WindowHeight = 340;

		public:
			WindowManager(HINSTANCE hInstance);
			~WindowManager();

			bool IsRunning() const;
			void Update();
			void Display();

		private:
			bool InitWindow();
			void CreateWindowClass();
			void ApplyDarkMode();
			void HandleWindowMessages();

			static LRESULT CALLBACK
			WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			HWND hWindow = nullptr;
			HINSTANCE hInstance = nullptr;
			WNDCLASSEXW mWindowClass = {0};

			DirectX11 mDx11;
			Imgui mImgui;

			BOOL bIsDarkMode = TRUE;
			bool bIsRunning = true;
			bool bIsWindowClassRegistered = false;
		};
	}
}
