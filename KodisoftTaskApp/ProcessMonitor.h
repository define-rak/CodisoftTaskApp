#include <windows.h>
#include <tchar.h>
#include <Psapi.h>
#include <string>
#include <fstream>
#include <ctime>

#pragma once

class Logger;

class ProcessMonitor
{
private:
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	LPSTR path;
	DWORD status;
	BOOL isLoopNeeded;

	Logger *log;

	enum { RUNNING = 0, STOPPED = 1, RESTARTING = 2 };

public:
	ProcessMonitor();
	ProcessMonitor(LPTSTR path);
	ProcessMonitor(DWORD pId);
	//~ProcessMonitor();

	HANDLE getProcessHandle();
	DWORD getProcessId();
	DWORD getStatus();
	LPSTR getPath();

	BOOL start();
	BOOL stop();
	BOOL restart();
};

class Logger
{
private:
	std::string path;
	std::ofstream log;

public:
	Logger();
	Logger(std::string path);
	~Logger();

	void writeMessage(ProcessMonitor &pm, std::string action);
};