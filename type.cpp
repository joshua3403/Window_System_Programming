/*
	type.exe.�� �������� ����
*/

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

void TYPE(TCHAR* fileName)	// For Redirection
{
	TCHAR StringBuff[1024];	// ���ڿ� ���� ���Ƿ� ����

	FILE* filePtr = _tfopen(fileName, _T("rt"));
	while (_fgetts(StringBuff, 1024, filePtr))
		_fputts(StringBuff, stdout);
}

int _tmain(int argc, TCHAR* argv[])
{
	if (argc < 2)
	{
		return -1;
	}

	TYPE(argv[1]);

	return 0;
}