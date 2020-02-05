/*
	CommandPrmpt_Two.cpp
	���α׷� ���� : ���� ������Ʈ 2��
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <locale.h>
#include <windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[]
= _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�. \n");

int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);

int _tmain(int agrc, TCHAR* argv[])
{
	// �ѱ� �Է��� ������ �ϱ� ����
	_tsetlocale(LC_ALL, _T("Korean"));

	DWORD isExit;
	while (1)
	{
		isExit = CmdProcessing();
		if (isExit == TRUE)
		{
			_fputts(_T("���ɾ� ó���� �����մϴ�. \n"), stdout);
			break;
		}
	}

	return 0;
}

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

/**************************************************************************
�Լ� : TCHAR int CmdProcessing(void)
��� : ���ɾ �Է� �޾Ƽ� �ش� ���ɾ �����Ǿ� �ִ� ����� �����Ѵ�.
		exit�� �ԷµǸ� TRUE�� ��ȯ�ϰ� �̴� ���α׷��� ����� �̾�����.
***************************************************************************/
int CmdProcessing(void)
{
	_fputts(_T("Best command prompt>> "), stdout);
	gets(cmdString);
	TCHAR* token = _tcstok(cmdString, seps);
	int tokenNum = 0;
	while (token != NULL)
	{
		_tcscpy_s(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("�߰� �Ǵ� ���ɾ� 1")))
	{

	}
	else if (!_tcscmp(cmdTokenList[0], _T("�߰� �Ǵ� ���ɾ� 2")))
	{

	}
	else
	{
		STARTUPINFO si = { 0, };
		PROCESS_INFORMATION pi;

		si.cb = sizeof(si);
		//SetCurrentDirectory(_T("C:\\WINDOWS\\system32"));
		BOOL isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

		if (isRun == FALSE)
			_tprintf(ERROR_CMD, cmdTokenList[0]);
	}
	return 0;
}

/**************************************************************************
�Լ� : TCHAR * StrLower(TCHAR *pStr)
��� : ���ڿ��� ���� �����ϴ� ��� �빮�ڸ� �ҹ��ڷ� �����Ѵ�.
		����� ���ڿ��� �����͸� ��ȯ�Ѵ�.
***************************************************************************/
TCHAR* StrLower(TCHAR* pStr)
{
	TCHAR* ret = pStr;

	while (*pStr)
	{
		if (_istupper(*pStr))
			*pStr = _totlower(*pStr);
		pStr++;
	}

	return ret;
}