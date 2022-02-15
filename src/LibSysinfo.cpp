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

bool LibSysinfo::GetOS(SYSINFO::OS& info)
{
	strcpy(info.name, impl->GetOS().c_str());
	return true;
}
