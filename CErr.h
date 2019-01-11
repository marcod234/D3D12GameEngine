#pragma once

class CErr 
{
  public:
    static void mfDieMessageBox(const wchar_t* msg);
    static void mfDieConsole(const wchar_t* msg);
};
