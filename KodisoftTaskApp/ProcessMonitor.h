#include <windows.h>
#include <tchar.h>

#pragma once

class ProcessMonitor
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	LPTSTR path;

public:
	ProcessMonitor();
	ProcessMonitor(LPTSTR path);
	~ProcessMonitor();

	void checkProcessStatus();
};

