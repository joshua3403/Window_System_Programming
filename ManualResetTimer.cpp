/*
	ManualResetTimer.cpp
	프로그램 설명 : 수동 리셋 타이머 오브젝트의 대한 이해
*/

#define _WIN32_WINNT	0x0400

#include "stdafx.h"

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));

	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());

		return 1;
	}

	_tprintf(_T("Waiting for 10 seconds...\n"));

	// 타이머의 알람을 10초로 설정
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, FALSE);


	// 타이머의 알람을 대기
	WaitForSingleObject(hTimer, INFINITE);
	_tprintf(_T("Timer was signaled.\n"));
	MessageBeep(MB_ICONEXCLAMATION);

	return 0;
}