/*
	KernalObjProb2.cpp
	프로그램 설명 : CloseHandle 함수 이해 2
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	DWORD n = 0;

	while (n < 100)
	{
		for (DWORD i = 0; i < 10000; i++)
		{
			for (DWORD i = 0; i < 10000; i++);	// Busy Waiting

			_fputts(_T("KernalObjProb2.exe \n"), stdout);
			n++;
		}
	}


	_fputts(_T("2번 프로세스 종료\n"), stdout);

	return 0;
}