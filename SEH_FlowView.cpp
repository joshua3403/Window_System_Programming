/*
	SEH_FLOWView.cpp
	���α׷� ���� : SEH�� ���� �帧 �ľ��ϱ�
*/

#include "stdafx.h"

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(_T("start point! \n"));

	int* p = NULL;

	__try
	{
		*p = 100;		// ���ܻ�Ȳ �߻�
		_tprintf(_T("value: %d \n"), *p);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)		// ����ó�� ��� ����
	{
		_tprintf(_T("exception occurred! \n"));
	}

	_tprintf(_T("end point! \n"));		// ����ó�� ���� ����

	return 0;
}