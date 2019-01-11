#include "CApp.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  return CApp::mfInstance()->mfWndProc(hWnd, message, wParam, lParam);
}

CApp* CApp::mvInstance = nullptr;

CApp::CApp(HINSTANCE hinstance)
{
  mvHInstance = hinstance;
  mvMainHwnd = 0;
  mvClientWidth = 800;
  mvClientHeight = 600;
}

CApp* CApp::mfInstance(HINSTANCE hinstance)
{
  if (!mvInstance) //only one instance of class
    mvInstance = new CApp(hinstance);

  return mvInstance;
}

bool CApp::mfInit()
{
  if (mvMakeConsole)
    mfMakeConsole();

  mfInitWindow();

  //if (!initDirectX())
  //  CErr::mfDieConsole(L"Could not initialize DirectX");

  return true;
}

//https://stackoverflow.com/questions/311955/redirecting-cout-to-a-console-in-windows
void CApp::mfMakeConsole()
{
  HANDLE in, out, err;
  int iFD, oFD, eFD;
  FILE *fi, *fo, *fe, *temp;

  if (!AllocConsole())
    CErr::mfDieConsole(L"Could not allocate console");

  freopen_s(&temp, "nul", "r", stdin);
  freopen_s(&temp, "nul", "w", stdout);
  freopen_s(&temp, "nul", "w", stderr);

  //stdin
  in = GetStdHandle(STD_INPUT_HANDLE);
  if (in == INVALID_HANDLE_VALUE)
    CErr::mfDieConsole(L"Could not get stdin handle");

  iFD = _open_osfhandle((intptr_t)in, _O_TEXT);
  if (iFD == -1)
    CErr::mfDieConsole(L"Could not get stdin file descriptor");

  fi = _fdopen(iFD, "r");
  if (fi == NULL)
    CErr::mfDieConsole(L"Could not open stdin file");

  int dI = _dup2(_fileno(fi), _fileno(stdin));
  if (dI != 0)
    CErr::mfDieConsole(L"Could not redirect stdin to console");
  setvbuf(fi, NULL, _IONBF, 0);

  //stdout
  out = GetStdHandle(STD_OUTPUT_HANDLE);
  if (out == INVALID_HANDLE_VALUE)
    CErr::mfDieConsole(L"Could not get stdin handle");

  oFD = _open_osfhandle((intptr_t)out, _O_TEXT);
  if (oFD == -1)
    CErr::mfDieConsole(L"Could not get stdout file descriptor");

  fo = _fdopen(oFD, "w");
  if (fo == NULL)
    CErr::mfDieConsole(L"Could not open stdout file");

  int dO = _dup2(_fileno(fo), _fileno(stdout));
  if (dO != 0)
    CErr::mfDieConsole(L"Could not redirect stdout to console");
  setvbuf(fi, NULL, _IONBF, 0);

  //sterr
  err = GetStdHandle(STD_ERROR_HANDLE);
  if (err == INVALID_HANDLE_VALUE)
    CErr::mfDieConsole(L"Could not get stderr handle");

  eFD = _open_osfhandle((intptr_t)err, _O_TEXT);
  if (eFD == -1)
    CErr::mfDieConsole(L"Could not get stderr file descriptor");

  fe = _fdopen(eFD, "w");
  if (fe == NULL)
    CErr::mfDieConsole(L"Could not open stderr file");

  int dE = _dup2(_fileno(fe), _fileno(stderr));
  if (dE != 0)
    CErr::mfDieConsole(L"Could not redirect stdout to console");
  setvbuf(fi, NULL, _IONBF, 0);

  std::ios::sync_with_stdio();
}

void CApp::mfInitWindow()
{
  WNDCLASS wc;

  RECT windowSize = { 0, 0, mvClientWidth, mvClientHeight };

  //window parameters
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = MainWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = mvHInstance;
  wc.hCursor = LoadCursor(0, IDC_ARROW);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = L"GameWndClass";
  wc.hIcon = LoadIcon(0, IDI_APPLICATION);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

  //register window
  if (!RegisterClass(&wc))
    CErr::mfDieConsole(L"Could not register window");

  //adjust the window rect such that the usable area
  //is given by mvClientWidth and mvClientHeight
  if (!AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, FALSE))
    CErr::mfDieConsole(L"Unable to adjust window");

  mvMainHwnd = CreateWindow(
    L"GameWndClass",
    mvWindowTitle,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, //top left x position
    CW_USEDEFAULT, //top left y position
    windowSize.right - windowSize.left, //width
    windowSize.bottom - windowSize.top, //height
    NULL, //parent window
    NULL, //menu handle
    mvHInstance, //application handle
    NULL); //data made available to WM_CREATE message handler

  if (mvMainHwnd == NULL)
    CErr::mfDieConsole(L"Could not create window");

  ShowWindow(mvMainHwnd, SW_SHOW);
  UpdateWindow(mvMainHwnd);
}


int CApp::mfRun()
{
  MSG msg = { 0 };

  while (msg.message != WM_QUIT)
  {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      //game stuff
    }
  }

  return (int)msg.wParam;
}

LRESULT CApp::mfWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  //main message loop
  switch (message)
  {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

  }

  //default window procedure
  return DefWindowProc(hWnd, message, wParam, lParam);
}