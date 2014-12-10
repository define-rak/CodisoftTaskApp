#include "ProcessMonitor.h"
#include <iostream>

using namespace std;

ProcessMonitor::ProcessMonitor()
{
	this->path = NULL;
	this->status = 1;
}

ProcessMonitor::ProcessMonitor(LPTSTR path)
{
	this->path = new TCHAR[sizeof(path) / sizeof(TCHAR)];
	lstrcpy((this->path), path);
	this->status = 1;
}

//void ProcessMonitor::runProcess()
//{
//	STARTUPINFO si;
//	PROCESS_INFORMATION pi;
//
//	ZeroMemory(&si, sizeof(si));
//	ZeroMemory(&pi, sizeof(si));
//	si.cb = sizeof(si);
//
//	if (this->status == STOPPED)
//	{
//		CreateProcess(NULL, this->path, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL,
//			&si, &pi);
//		this->status = WORKING;
//	}
//
//	this->si = si;
//	this->pi = pi;
//}
//
//void ProcessMonitor::stopProcess()
//{
//	HANDLE hProcess = pi.hProcess;
//	HANDLE hThread = pi.hThread;
//
//	if (this->status == WORKING)
//	{
//		CloseHandle(hProcess);
//		CloseHandle(hThread);
//	}
//}
//
//ProcessMonitor::~ProcessMonitor()
//{
//}

BOOL WINAPI ProcessMonitor::start()
{
	ZeroMemory(&(this->si), sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&(this->pi), sizeof(pi));
	if (!CreateProcess(NULL, this->path, NULL, NULL,
		FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &(this->si), &(this->pi)))
	{
		//fputs(format("process::start(...) failed [%d]\n", GetLastError()), stderr);
		return false;
	}

	//WaitForSingleObject(pi.hProcess, INFINITE);
	//CloseHandle(pi.hProcess);
	//CloseHandle(pi.hThread);
	return true;
}