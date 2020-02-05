#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char* argv[])
{
	int i;
	for (i = 0; i < argc; ++i)
		fputws(argv[i], stdout);	// char* argv[]는 MBCS 기반으로 구성된 문자열

	return 0;
}