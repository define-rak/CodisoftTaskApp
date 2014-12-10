#include <windows.h>
#include <tchar.h>


#pragma once

class ProcessMonitor
{
private:
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	LPSTR path;
	DWORD status;

public:
	ProcessMonitor();
	ProcessMonitor(LPTSTR path);
	//~ProcessMonitor();

	BOOL WINAPI start();
	BOOL __stdcall stop();
	
};

