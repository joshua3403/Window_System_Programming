/*
	NamedMutex.cpp
	프로그램 설명 : named Mutex의 역할 이해
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

HANDLE hMutex;
DWORD dwWaitResult;

void ProcessBaseCriticalSection()
{
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
		// 쓰레드가 뮤텍스를 소유하였다.
	case WAIT_OBJECT_0:
		_tprintf(_T("thread got mutex! \n"));
		break;
		
		// time_out이 발생했다.
	case WAIT_TIMEOUT:
		_tprintf(_T("timer expired !\n"));
		break;

		// 뮤택스 반환이 적절히 이루어지지 않았다.
	case WAIT_ABANDONED:
		return;
	}
	for (DWORD i = 0; i < 5; i++)
	{
		_tprintf(_T("Thread Running!\n"));
		Sleep(10000);
	}

	ReleaseMutex(hMutex);
}

int _tmain(int argc, TCHAR* argv[])
{
#if 0
	hMutex = CreateMutex(
		NULL, FALSE, _T("NamedMutex"));
#else
	hMutex = OpenMutex(MUTEX_ALL_ACCESS,
		FALSE,
		_T("NamedMutex"));
#endif
	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error: %d \n"), GetLastError());
		return -1;
	}

	ProcessBaseCriticalSection();

	CloseHandle(hMutex);

	return 0;
	
}