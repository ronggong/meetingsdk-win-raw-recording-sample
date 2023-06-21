#include "stdafx.h"

#include "Config.h"
#include "sdk_demo_app.h"

using namespace DuiLib;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR lpCmdLine, int nCmdShow)
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	
	g_demoApp.Run(hInstance);

	if (std::strlen(lpCmdLine))
	{
		auto* config = &Config::getInstance();
		config->parseJoinUrl(lpCmdLine);
	}
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (WM_QUIT == msg.message)
		{
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	g_demoApp.Cleanup();
	return 0;
}