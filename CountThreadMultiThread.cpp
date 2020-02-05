/*
	CountThreadMultiThread.cpp
	프로그램 설명 : _beginthreadex 함수 기반으로 변경
*/

#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <windows.h>

#define MAX_THREADS (1024*10)

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (true)
	{
		_tprintf(_T("thread num : %d \n"), threadNum);
		Sleep(1000);
	}

	return 0;
}

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	// 생성 가능한 최대 개수의 쓰레드 생성

	while (true)
	{
		hThread[cntOfThread] =
			(HANDLE)_beginthreadex(
				NULL,
				0,
				ThreadProc,
				(LPVOID)cntOfThread,
				0,
				(unsigned int*)&dwThreadID[cntOfThread]
			);

		// 쓰레드 생성 확인
		if (hThread[cntOfThread] == NULL)
		{
			_tprintf(_T("MAXIMUM THREAD SIZE : %d \n"), cntOfThread);
			break;
		}

		cntOfThread++;
	}

	for (DWORD i = 0; i < cntOfThread; ++i)
	{
		CloseHandle(hThread[i]);
	}

	return 0;
}