#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char* argv[])
{
	int i;
	for (i = 0; i < argc; ++i)
		fputws(argv[i], stdout);	// char* argv[]�� MBCS ������� ������ ���ڿ�

	return 0;
}