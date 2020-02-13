/*
	SEH_FLOWView.cpp
	프로그램 설명 : SEH의 실행 흐름 파악하기
*/

#include "stdafx.h"

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(_T("start point! \n"));

	int* p = NULL;

	__try
	{
		*p = 100;		// 예외상황 발생
		_tprintf(_T("value: %d \n"), *p);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)		// 예외처리 방식 결정
	{
		_tprintf(_T("exception occurred! \n"));
	}

	_tprintf(_T("end point! \n"));		// 예외처리 이후 실행

	return 0;
}