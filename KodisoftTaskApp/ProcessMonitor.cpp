#include "ProcessMonitor.h"
#include <iostream>

using namespace std;

ProcessMonitor::ProcessMonitor()
{
	this->path = NULL;

	ZeroMemory(&(this->si), sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&(this->pi), sizeof(pi));

	this->status = STOPPED;
	
	this->isLoopNeeded = TRUE;
}

ProcessMonitor::ProcessMonitor(LPTSTR path)
{
	this->path = new TCHAR[sizeof(path) / sizeof(TCHAR)];
	lstrcpy((this->path), path);

	ZeroMemory(&(this->si), sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&(this->pi), sizeof(pi));

	this->status = STOPPED;

	this->isLoopNeeded = TRUE;
}

ProcessMonitor::ProcessMonitor(DWORD pId)
{
	DWORD pid = 6816;
	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	LPSTR s = new TCHAR[256];
	GetModuleFileNameEx(h, NULL, s, 256);
}

//

HANDLE ProcessMonitor::getProcessHandle()
{
	return (this->pi).hProcess;
}

DWORD ProcessMonitor::getProcessId()
{
	return (this->pi).dwProcessId;
}

DWORD ProcessMonitor::getStatus()
{
	return this->status;
}

//

BOOL ProcessMonitor::start()
{
	if (this->status == STOPPED)
	{
		if (!CreateProcess(NULL, this->path, NULL, NULL,
			FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &(this->si), &(this->pi)))
		{
			this->status = STOPPED;
			return FALSE;
		}

		this->status = RUNNING;
	}

	while (WaitForSingleObject(pi.hProcess, INFINITE) == WAIT_OBJECT_0)
	{
		if (this->isLoopNeeded == FALSE)
		{
			return FALSE;
		}

		this->status = RESTARTING;

		if (!CreateProcess(NULL, this->path, NULL, NULL,
			FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &(this->si), &(this->pi)))
		{
			this->status = STOPPED;
			return TRUE;
		}
		else
		{
			this->status = RUNNING;
		} 
	}
}

BOOL ProcessMonitor::stop()
{
	if (this->status == RUNNING)
	{
		if (!TerminateProcess((this->pi).hProcess, EXIT_SUCCESS))
		{
			this->status = STOPPED;
			CloseHandle(this->pi.hProcess);
			CloseHandle(this->pi.hThread);
			return FALSE;
		}

		return TRUE;
	}
	return FALSE;
}