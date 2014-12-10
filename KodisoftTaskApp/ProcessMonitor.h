#include <windows.h>
#include <tchar.h>
#include <Psapi.h>

#pragma once

class ProcessMonitor
{
private:
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	LPSTR path;
	DWORD status;
	BOOL isLoopNeeded;

	enum {RUNNING = 0, STOPPED = 1, RESTARTING = 2};

public:
	ProcessMonitor();
	ProcessMonitor(LPTSTR path);
	ProcessMonitor(DWORD pId);
	//~ProcessMonitor();

	HANDLE getProcessHandle();
	DWORD getProcessId();
	DWORD getStatus();

	BOOL start();
	BOOL stop();
	BOOL restart();
};

