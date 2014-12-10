#include <windows.h>
#include <iostream>
#include <tchar.h>
#include "ProcessMonitor.h"

using namespace std;

int main()
{

	ProcessMonitor my("c:\\windows\\notepad.exe");
	my.start();
	cout << my.stop();

	system("pause");

	return 0;
}