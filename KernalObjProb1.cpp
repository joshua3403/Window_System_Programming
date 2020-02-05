/*
	KernalObjProb1.cpp
	프로그램 설명 : CloseHandle 함수 이해1
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("KernalObjProb2.exe");
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	CloseHandle(pi.hProcess);
	_fputts(_T("1번 프로세스 종료"), stdout);
	return 0;
}