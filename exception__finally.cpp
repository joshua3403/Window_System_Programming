/*
	exception_finally
	���α׷� ���� : ���� �ڵ鷯 ����
*/

#include "stdafx.h"

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR str[2];

	__try
	{
		_tcscpy_s(str, _T("AASDFWEFASDFASDGAHDFGH"));
		_tprintf(_T("%s \n"), str);
	}
	__finally
	{
		_tprintf(_T("__finally block! \n"));
	}

	return 0;
}