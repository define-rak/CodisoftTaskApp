#include "ProcessMonitor.h"
#include <cstdio>

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
	ZeroMemory(&(this->si), sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&(this->pi), sizeof(pi));

	(this->pi).dwProcessId = pId;
	(this->pi).hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (this->pi).dwProcessId);

	if ((this->pi).hProcess != 0)
	{
		this->path = new TCHAR[256];
		GetModuleFileNameEx((this->pi).hProcess, NULL, this->path, 256);
		printf("%s", this->path);
		this->status = RUNNING;
		this->isLoopNeeded = TRUE;		
	}
	else
	{
		this->status = STOPPED;
	}
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

LPSTR ProcessMonitor::getPath()
{
	return this->path;
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
		(this->log)->writeMessage(*this, "Start");
	}

	while (WaitForSingleObject((this->pi).hProcess, INFINITE) == WAIT_OBJECT_0)
	{
		(this->log)->writeMessage(*this, "Crash");
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
			(this->log)->writeMessage(*this, "Start");
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
			(this->log)->writeMessage(*this, "Manual shutdown");
			return FALSE;
		}

		return TRUE;
	}
	return FALSE;
}

//
//
//

Logger::Logger()
{
	
}

Logger::Logger(std::string path)
{
	this->path = path;
	(this->log).open((this->path).c_str());
}

Logger::~Logger()
{
	(this->path).erase();
	(this->log).close();
}

//

void Logger::writeMessage(ProcessMonitor &pm, std::string action)
{
	(this->log) << action.c_str() << "," << std::time(0) << "," << pm.getPath() << "," << pm.getProcessHandle() << "," << pm.getProcessId() << std::endl;
}

