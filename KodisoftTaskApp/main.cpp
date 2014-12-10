#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include "ProcessMonitor.h"
#include <Psapi.h>

using namespace std;

int main()
{

	ProcessMonitor my("c:\\windows\\notepad.exe");
	//my.start();
	//my.stop();

	DWORD pid = 6816;
	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	LPSTR s = new TCHAR[256];
	GetModuleFileNameEx(h, NULL, s, 256);
	printf("%s", s);

	system("pause");

	return 0;
}