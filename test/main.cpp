#include "lib-sysinfo/LibSysinfo.h"
#include <iostream>

int main(int argc, char* argv[])
{
	LibSysinfo sysinfo;
	SYSINFO info;
	sysinfo.Initialize();
	sysinfo.GetOS(info.os);
	std::cout << info.os.name << std::endl;
	sysinfo.Release();

	return 0;
}