#include "LibSysinfoImpl.h"
#include "COMBuilder.h"
#include "WMIBuilder.h"

LibSysinfoImpl::LibSysinfoImpl()
{
	com = std::make_shared<COMBuilder>();
	wmi = std::make_shared<WMIBuilder>();
}
LibSysinfoImpl::~LibSysinfoImpl()
{
	wmi.reset();
	com.reset();
}
bool LibSysinfoImpl::Initialize()
{
	if (!com->Initialize())
		0; // return false;

	if (!wmi->Initialize())
		return false;

	return true;
}
bool LibSysinfoImpl::Release()
{
	wmi->Release();
	com->Release();
	return true;
}
std::string LibSysinfoImpl::GetOS()
{
	auto tmp = wmi->ExecWQL({ "Name", "OSArchitecture" }, "Win32_OperatingSystem");
	if (tmp.size() < 1)
		return "UNKNOWN";

	// only get last one os info
	std::vector<std::string>& back = tmp.back();

	return std::move(back[0].erase(back[0].find("|")) + " " + back[1]);
}
