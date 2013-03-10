// win program entry
//#include <stdio.h>
//#include <math.h>

#include "Selene/Application/seMain.h"
#include "Selene/Application/seApplication.h"
#include "Selene/Application/seAppConfig.h"

#include "Selene/Render/seGraphics.h"

#include "Selene/Utils/seUtils.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

namespace Selene
{
	class CWinParams
	{
	public:
		HGLRC m_RC;
		HDC m_DC;
		HWND m_Wnd;
		HINSTANCE m_Instance;
		bool m_Active;
		bool m_Fullscreen;
		CApplication* m_pApp;

	public:
		CWinParams()
			:m_RC(NULL)
			,m_DC(NULL)
			,m_Wnd(NULL)
			,m_Instance(NULL)
			,m_Active(false)
			,m_pApp(NULL)
		{
		}
	};

	static CWinParams g_Params;

	void KillGLWindow();
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	bool CreateGLWindow(const char* title, int width, int height, int bits, bool fullscreenFlag)
	{
		int pixelFormat = 0;
		DWORD windowExStyle;
		DWORD windowStyle;
		RECT windowRect;

		windowRect.left = 0;
		windowRect.right = width;
		windowRect.top = 0;
		windowRect.bottom = height;

		g_Params.m_Fullscreen = fullscreenFlag;
		g_Params.m_Instance = GetModuleHandle(NULL);

		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = g_Params.m_Instance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = "SeleneWindow";

		if (!RegisterClass(&wc))
		{
			MessageBox(NULL, "Could not register class!", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		if (g_Params.m_Fullscreen)
		{
			DEVMODE screenSettings;
			memset(&screenSettings, 0, sizeof(screenSettings));
			screenSettings.dmSize = sizeof(screenSettings);
			screenSettings.dmPelsWidth = width;
			screenSettings.dmPelsHeight = height;
			screenSettings.dmBitsPerPel = bits;
			screenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
			if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				if (MessageBox(NULL, "Could not switch to fullscreen! Run in window?",
							   "Error",
							   MB_YESNO | MB_ICONEXCLAMATION) == MB_YESNO)
				{
					g_Params.m_Fullscreen = false;
				}
				else
				{
					MessageBox(NULL, "Progam will quit.", "Error", MB_OK | MB_ICONEXCLAMATION);
					return false;
				}
			}
		}

		if (g_Params.m_Fullscreen)
		{
			windowExStyle = WS_EX_APPWINDOW;
			windowStyle = WS_POPUP;
			ShowCursor(false);
		}
		else
		{
			windowExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			windowStyle = WS_OVERLAPPEDWINDOW;
		}

		AdjustWindowRectEx(&windowRect, windowStyle, false, windowExStyle);

		g_Params.m_Wnd = CreateWindowEx(windowExStyle,
							  "SeleneWindow",
							  title,
							  windowStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
							  0,
							  0,
							  windowRect.right - windowRect.left,
							  windowRect.bottom - windowRect.top,
							  NULL,
							  NULL,
							  g_Params.m_Instance,
							  NULL);
		if (g_Params.m_Wnd == NULL)
		{
			KillGLWindow();
			MessageBox(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		static PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			bits,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			32,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		g_Params.m_DC = GetDC(g_Params.m_Wnd);
		if (g_Params.m_DC == NULL)
		{
			KillGLWindow();
			MessageBox(NULL, "Could not get DC!", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		pixelFormat = ChoosePixelFormat(g_Params.m_DC, &pfd);
		if (pixelFormat == 0)
		{
			KillGLWindow();
			MessageBox(NULL, "Could not find requested pixel format!", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!SetPixelFormat(g_Params.m_DC, pixelFormat, &pfd))
		{
			KillGLWindow();
			MessageBox(NULL, "Could not set pixel format!", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		g_Params.m_RC = wglCreateContext(g_Params.m_DC);
		if (g_Params.m_RC == NULL)
		{
			KillGLWindow();
			MessageBox(NULL, "Could not create RC!", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!wglMakeCurrent(g_Params.m_DC, g_Params.m_RC))
		{
			KillGLWindow();
			MessageBox(NULL, "Could not activate RC!", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		ShowWindow(g_Params.m_Wnd, SW_SHOW);
		SetForegroundWindow(g_Params.m_Wnd);
		SetFocus(g_Params.m_Wnd);

		ASSERT(g_Params.m_pApp != NULL, "App is null!");
		CGraphics* pGraphics = g_Params.m_pApp->GetGraphics();
		ASSERT(pGraphics != NULL, "Graphics is null!");
		pGraphics->PrepareView(width, height);

		if (!pGraphics->Init())
		{
			KillGLWindow();
			MessageBox(NULL, "Could not init Graphics!", "Error", MB_OK | MB_ICONERROR);
			return false;
		}

		return true;
	}

	void KillGLWindow()
	{
		if (g_Params.m_Fullscreen)
		{
			ChangeDisplaySettings(NULL, 0);
			ShowCursor(true);
		}
		if (g_Params.m_RC != NULL)
		{
			if (!wglMakeCurrent(NULL, NULL))
			{
				MessageBox(NULL, "Release of RC and DC failed!", "Error", MB_OK | MB_ICONERROR);
			}
			if (!wglDeleteContext(g_Params.m_RC))
			{
				MessageBox(NULL, "Delete of RC failed!", "Error", MB_OK | MB_ICONERROR);
			}
			g_Params.m_RC = NULL;
		}
		if (g_Params.m_DC != NULL)
		{
			if (!ReleaseDC(g_Params.m_Wnd, g_Params.m_DC))
			{
				MessageBox(NULL, "Release of DC failed!", "Error", MB_OK | MB_ICONERROR);
			}
			g_Params.m_DC = NULL;
		}
		if (g_Params.m_Wnd != NULL)
		{
			if (!DestroyWindow(g_Params.m_Wnd))
			{
				MessageBox(NULL, "Release of hWnd failed!", "Error", MB_OK | MB_ICONERROR);
			}
			g_Params.m_Wnd = NULL;
		}
		if (!UnregisterClass("SeleneWindow", g_Params.m_Instance))
		{
			MessageBox(NULL, "Could not unregister class!", "Error", MB_OK | MB_ICONERROR);
		}
		g_Params.m_Instance = NULL;
	}

	LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_ACTIVATE:
			g_Params.m_Active = !HIWORD(wParam);
			return 0;

		case WM_SYSCOMMAND:
			switch (wParam)
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				return 0;
			}
			break;

		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			//keys[wParam] = true;
			return 0;

		case WM_KEYUP:
			//keys[wParam] = false;
			return 0;

		case WM_SIZE:
			ASSERT(g_Params.m_pApp != NULL, "App is null!");
			ASSERT(g_Params.m_pApp->GetGraphics() != NULL, "Graphics is null!");
			g_Params.m_pApp->GetGraphics()->PrepareView(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}

		return DefWindowProc(wnd, msg, wParam, lParam);
	}

} // namespace Selene

// Program Entry (WinMain)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	bool done = false;

	Selene::CApplication app;
	Selene::g_Params.m_pApp = &app;

	// entry
	Selene::Entry(app);

	// process command line arguments
	int cmdLineLength = strlen(lpCmdLine);
	int iArgC = 0;
	char** astrArgV = NULL;
	char* strCmdLine = NULL;
	if (cmdLineLength == 0)
	{
		iArgC = 0;
		astrArgV = new char*[1];
		astrArgV[0] = "";
		strCmdLine = new char[1];
		strCmdLine[0] = 0;
	}
	else
	{
		strCmdLine = new char[cmdLineLength + 1];
		strcpy_s(strCmdLine, cmdLineLength + 1, lpCmdLine);
		int iIndex = 0;
		char* strToken = NULL;
		char* strNextToken = NULL;
		strToken = strtok_s(strCmdLine, " ", &strNextToken);
		while (strToken != NULL)
		{
			iIndex++;
			strToken = strtok_s(NULL, " ", &strNextToken);
		}
		iArgC = iIndex;
		astrArgV = new char*[iArgC];
		strcpy_s(strCmdLine, cmdLineLength + 1, lpCmdLine);
		strNextToken = NULL;
		strToken = strtok_s(strCmdLine, " ", &strNextToken);
		iIndex = 0;
		while (strToken != NULL)
		{
			astrArgV[iIndex] = strToken;
			iIndex++;
			strToken = strtok_s(NULL, " ", &strNextToken);
		}
	}
	app.ParseCommandLine(iArgC, astrArgV);
	SAFE_DELETE_ARRAY(astrArgV);
	SAFE_DELETE_ARRAY(strCmdLine);

	Selene::CAppConfig* pAppConfig = app.GetAppConfig();
	if (!Selene::CreateGLWindow(pAppConfig->GetAppName(),
								pAppConfig->GetWindowWidth(),
								pAppConfig->GetWindowHeight(),
								32,
								pAppConfig->GetFullscreen()))
	{
		return 0;
	}

	app.Init();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (Selene::g_Params.m_Active)
			{
				if (app.ShouldQuit())
				{
					done = true;
				}
				else
				{
					app.Loop();
					SwapBuffers(Selene::g_Params.m_DC);
				}
			}
		}
	}

	app.Terminate();

	Selene::KillGLWindow();
	return 0;
}
