#include "ProcessMonitor.h"


ProcessMonitor::ProcessMonitor()
{
	ZeroMemory(&(this->si), sizeof(this->si));
	ZeroMemory(&(this->pi), sizeof(this->si));
	(this->si).cb = sizeof(this->si);
	(this->path) = NULL;
}

ProcessMonitor::ProcessMonitor(LPTSTR path)
{
	ZeroMemory(&(this->si), sizeof(this->si));
	ZeroMemory(&(this->pi), sizeof(this->si));
	(this->si).cb = sizeof(this->si);
	(this->path) = new TCHAR[sizeof(path) / sizeof(TCHAR)];
	lstrcpy((this->path), path);
}

void ProcessMonitor::checkProcessStatus()
{

}

ProcessMonitor::~ProcessMonitor()
{
	CloseHandle((this->pi).hProcess);
	CloseHandle((this->pi).hThread);
}

