// CFGame.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CFGame.h"
#include "CFApp.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CFApp theApp(hInstance);

	if (!theApp.Init())
		return 0;

	return theApp.Run();
}


