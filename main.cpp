#include "CApp.h"
#include "CErr.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CApp* app = CApp::mfInstance(hInstance);
	if (app == nullptr)
		CErr::mfDieConsole(L"Could not allocate app");

	if (!app->mfInit())
		CErr::mfDieConsole(L"Could not initialize app");

	return app->mfRun();
}