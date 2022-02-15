#pragma once
#include <string>
#include "lib-sysinfo/SYSINFO.h"

#ifdef LIBSYSINFO_EXPORT
#define LIBSYSINFO_API __declspec(dllexport)
#else
#define LIBSYSINFO_API __declspec(dllimport)
#endif // LIBSYSINFO_EXPORT

class LibSysinfoImpl;
class __declspec(dllexport) LibSysinfo
{
public:
	LibSysinfo();
	~LibSysinfo();
	bool Initialize();
	bool Release();

	bool GetOS(SYSINFO::OS& info);

private:
	LibSysinfoImpl* impl = nullptr;
};