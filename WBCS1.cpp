#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	wchar_t str[] = L"ABC";
	int size = sizeof(str);
	int len = wcslen(str);

	printf("배열의 크기 : %d\n", size);
	printf("문자열 길이 : %d\n", len);

	return 0;