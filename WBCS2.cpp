#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	wchar_t str[] = L"ABC";
	int size = sizeof(str);
	int len = wcslen(str);

	wprintf(L"Array Size : ", size);
	wprintf(L"String Length L ", len);

	return 0;
}