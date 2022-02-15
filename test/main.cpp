#include "lib-sysinfo/LibSysinfo.h"
#include <iostream>

int main(int argc, char* argv[])
{
	LibSysinfo sysinfo;

	sysinfo.Initialize();
	std::cout << sysinfo.GetOS().c_str() << std::endl;
	sysinfo.Release();

	return 0;
}