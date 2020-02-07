/*
	ThreadPooling.cpp
	프로그램 설명 : 쓰레드 풀의 동작 원리 이해
*/

#include "stdafx.h"

#define WORK_MAX 10000
#define THREAD_MAX 50

typedef void (*WORK) (void);

DWORD AddWorkToPool(WORK work);
WORK GetWorkFromPool(void);
DWORD MakeThreadToPool(DWORD numOfThread);
void WorkerThreadFunction(LPVOID pParam);

typedef struct __WorkerThread
{
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;

// Work와 Thread 관리를 위한 구조체
struct __ThreadPool
{
	// Work을 등록하기 위한 배열
	WORK workList[WORK_MAX];

	// Thread 정보와 각 Thread별 Event 오브젝트
	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];

	// Work에 대한 정보
	DWORD idxOfCurrentWork;		// 대기 1순위 Work Index
	DWORD idxOfLastAddedWork;	// 마지막 추가 Work Index + 1

	// Nmber of Thread
	DWORD threadIdx;			// Pool에 존재하는 Thread의 개수
} gThreadPool;


//************************************************
// Mutex 관련 함수들
// gThreadPool에 대한 접근을 보호하기 위해 정의
//************************************************

static HANDLE mutex = NULL;


void InitMutex()
{
	mutex = CreateMutex(NULL, FALSE, NULL);
}

void DeInitMutex()
{
	BOOL ret = CloseHandle(mutex);
}

void AcquireMutex()
{
	DWORD ret = WaitForSingleObject(mutex, INFINITE);

	if (ret == WAIT_FAILED)
	{
		_tprintf(_T("Error Occur! \n"));
	}
}

void ReleaseMutex()
{
	BOOL ret = ReleaseMutex(mutex);
	if (ret == 0)
	{
		_tprintf(_T("Error Occur! \n"));
	}
}

//************************************************
// Thread Pool에 Work을 등록시키기 위한 함수
//************************************************

DWORD AddWorkToPool(WORK work)
{
	AcquireMutex();
	if (gThreadPool.idxOfLastAddedWork >= WORK_MAX)
	{
		_tprintf(_T("AddWorkToPool fail! \n"));
		return NULL;
	}

	// WORK 등록
	gThreadPool.workList[gThreadPool.idxOfLastAddedWork++] = work;

	// WORK 등록 후, 대기중인 모든 쓰레드들을 깨워 일을 시작하도록 함
	// 모두 깨울 필요가 없으므로 정교함이 떨어짐
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++)
	{
		DWORD ret = gThreadPool.workerThreadList[i].hThread;
		if (ret == WAIT_FAILED)
		{
			SetEvent(gThreadPool.workerEventList[i]);
			break;
		}
		//SetEvent(gThreadPool.workerEventList[i]);
	}

	ReleaseMutex();
	return 1;
}

//************************************************
// Thread에 Work를 배정하기위한 함수
// gThreadPool에 대한 접근을 보호하기 위해 정의
//************************************************
WORK GetWorkFromPool()
{
	WORK work = NULL;

	AcquireMutex();

	// 현재 처리해야 할 Work가 존재하지 않는다면
	if (!(gThreadPool.idxOfCurrentWork < gThreadPool.idxOfLastAddedWork))
	{
		ReleaseMutex();
		return NULL;
	}

	work = gThreadPool.workList[gThreadPool.idxOfCurrentWork++];
	ReleaseMutex();

	return work;
}

//************************************************
// Thread Pool 생성
// 전달되는 인자값에 따라 Thread 생성
//************************************************
DWORD MakeThreadToPool(DWORD numOfThread)
{
	InitMutex();
	DWORD capacity = WORK_MAX - (gThreadPool.threadIdx);

	if (capacity < numOfThread)
		numOfThread = capacity;

	for (DWORD i = 0; i < numOfThread; i++)
	{
		DWORD idThread;
		HANDLE hThread;

		gThreadPool.workerEventList[gThreadPool.threadIdx] = CreateEvent(NULL, FALSE, FALSE, NULL);

		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkerThreadFunction, (LPVOID)gThreadPool.threadIdx, 0, &idThread);

		gThreadPool.workerThreadList[gThreadPool.threadIdx].hThread = hThread;

		gThreadPool.workerThreadList[gThreadPool.threadIdx].idThread = idThread;

		gThreadPool.threadIdx++;
	}

	return numOfThread;
}

// 전달 되어야 할 대상
void WorkerThreadFunction(LPVOID pParam)
{
	WORK workFunction;
	HANDLE event = gThreadPool.workerEventList[(DWORD)pParam];

	while (1)
	{
		workFunction = GetWorkFromPool();
		if (workFunction == NULL)
		{
			// Work가 할당될 때까지 Block 상태에 놓이게 된다.
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		workFunction();
	}
}

// Simple Work Function
void TestFunction()
{
	// i는 static이므로 둘 이 상의 쓰레드에 의해 동시 접근이 가능하다.
	// 따라서 동기화가 필요하지만 동기화를 생략한다.
	static int i = 0;

	AcquireMutex();
	i++;

	_tprintf(_T("Good Test --%d : Processing thread : %d --\n\n"), i, GetCurrentThreadId);
	ReleaseMutex();

}

int _tmain(int argc, TCHAR* argv[])
{
	MakeThreadToPool(3);


	// 다수의 Work를 등록
	for (int i = 0; i < 100; i++)
	{
		AddWorkToPool(TestFunction);
	}

	Sleep(50000);

	DeInitMutex();

	return 0;
}