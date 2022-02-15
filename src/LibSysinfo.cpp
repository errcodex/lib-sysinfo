#include "lib-sysinfo/LibSysinfo.h"
#include "LibSysinfoImpl.h"

LibSysinfo::LibSysinfo()
{
	impl = new LibSysinfoImpl;
}

LibSysinfo::~LibSysinfo()
{
	if (impl)
		delete impl;
}

bool LibSysinfo::Initialize()
{
	return impl->Initialize();
}

bool LibSysinfo::Release()
{
	return impl->Release();
}

std::string LibSysinfo::GetOS()
{
	return impl->GetOS();
}
