#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	wchar_t str[] = L"ABC";
	int size = sizeof(str);
	int len = wcslen(str);

	printf("�迭�� ũ�� : %d\n", size);
	printf("���ڿ� ���� : %d\n", len);

	return 0;