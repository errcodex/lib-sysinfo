#pragma once
#include <string>

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

	std::string GetOS();

private:
	LibSysinfoImpl* impl = nullptr;
};