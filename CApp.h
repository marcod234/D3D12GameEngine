#pragma once

#include <Windows.h>
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include "CErr.h"


//singleton class, acts as entry point for game
class CApp 
{
  private:
    static CApp* mvInstance;
    HINSTANCE mvHInstance;
    HWND mvMainHwnd;
    int mvClientWidth, mvClientHeight;
    const wchar_t* mvWindowTitle = L"D3D12 GameEngine";

    CApp(HINSTANCE hinstance);
    CApp(CApp const &) = delete;
    CApp& operator=(CApp const &) = delete;

	public:

    bool mvMakeConsole = true;

    static CApp* mfInstance(HINSTANCE hinstance = nullptr);
    bool mfInit();
    void mfMakeConsole();
    void mfInitWindow();
    int mfRun();
    LRESULT mfWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};