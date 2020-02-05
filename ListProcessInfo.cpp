/*
	ListProcessInfo.cpp
	프로그램 설명 : 현재 실행 중인 프로세스 정보 출력
*/

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <TlHelp32.h>

int _tmain(int argc, TCHAR* argv[])
{
	// 현재 실행 중인 프로세스의  사진을 찍으라는 의미, 프로세스 정보를 함수 호출 시점 기준으로 추출
	// 찍고 싶은 프로세스 ID를 지정할 수 있는데 0이면 모든 프로세스를 대상으로 정볼르 추출한다.
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("CreateToolhelp32Snapshot error! \n"));
		return -1;
	}

	// 프로세스 정보를 얻기 위한 구조체 변수
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		_tprintf(_T("Process32First error!"));
		CloseHandle(hProcessSnap);
		return -1;
	}

	do
	{
		// 프로세스 이름, ID 정보 출력
		_tprintf(_T("%25s %5d \n"), pe32.szExeFile, pe32.th32ParentProcessID);
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return 0;

}