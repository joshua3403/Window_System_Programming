#include <iostream>
#include <string.h>
using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);
	}

	return 0;
}