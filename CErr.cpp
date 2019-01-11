#include <Windows.h>
#include <iostream>
#include "CErr.h"

void CErr::mfDieMessageBox(const wchar_t* msg)
{
    int msgboxID = MessageBox(NULL, msg, L"Error", MB_ICONERROR | MB_OK );

    if (msgboxID == IDOK)
    {
      exit(0);
    }

    //return msgboxID;
}

void CErr::mfDieConsole(const wchar_t* msg)
{
  wchar_t c;

  std::wcout << msg << std::endl << L"Enter anything to exit ...";
  std::wcin >> c;
  exit(0);
}