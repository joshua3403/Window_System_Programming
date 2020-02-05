/*
	StringEvent.cpp
	프로그램 설명 : 1. 생산자/소비자 모델의 이해
					2. 동기화 event에 대한 이해
*/

#include "stdafx.h"

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hThread;
	DWORD dwThreadID;

	hEvent = CreateEvent(
		NULL,				// 상속 불가
		TRUE,				// manual-rest 모드
		FALSE,				// non-signaled 상태
		NULL				// 이름 없는 event;
	);

	if (hEvent == NULL)
	{
		_tprintf(_T("Event object creation error \n"), stdout);
		return -1;
	}

	hThread = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadID);

	if (hThread == 0)
	{
		_fputts(_T("Thread creation error \n"), stdout);
		return -1;
	}

	_fputts(_T("Insert string: "), stdout);
	_fgetts(string, 30, stdin);

	SetEvent(hEvent);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hEvent);
	CloseHandle(hThread);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	// event가 signaled 상태가 되기를 바란다.
	WaitForSingleObject(hEvent, INFINITE);

	_fputts(_T("Output string : "), stdout);
	_fputts(string, stdout);

	return 0;
}