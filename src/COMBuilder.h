#define _WIN32_DCOM
#include <iostream>
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

class COMBuilder
{
public:
	bool Initialize()
	{
		if (!InitializeCOM() || !SetLevel())
			return false;
		return true;
	}

	bool Release()
	{
		CoUninitialize();
		return true;
	}

private:
	HRESULT hr;

	// 通过调用CoInitializeEx来初始化 COM
	// 调用CoInitializeEx是设置 COM 接口的标准过程。因此，WMI 不需要您在调用CoInitializeEx时遵守任何其他过程。有关详细信息，请参阅COM。
	bool InitializeCOM()
	{
		hr = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hr))
		{
			std::cout << "Failed to initialize COM library. Error code = 0x"
					  << std::hex << hr << std::endl;
			return false;
		}
		return true;
	}

	// 通过调用CoInitializeSecurity接口设置通用 COM 安全级别。
	// CoInitializeSecurity是为进程设置 COM 接口时必须调用的标准函数。如果要为整个进程的身份验证、模拟或身份验证服务设置默认安全设置，请调用CoInitializeSecurity 。有关详细信息，请参阅设置客户端应用程序进程安全性。如果要设置或更改特定代理的安全性，则必须调用CoSetProxyBlanket。在您无法控制身份验证、模拟或身份验证服务的默认安全设置的另一个进程中运行时，当您必须设置或更改 COM 安全性时，请使用CoSetProxyBlanket
	bool SetLevel()
	{
		hr = CoInitializeSecurity(
			NULL,						 // Security descriptor
			-1,							 // COM negotiates authentication service
			NULL,						 // Authentication services
			NULL,						 // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,	 // Default authentication level for proxies
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation level for proxies
			NULL,						 // Authentication info
			EOAC_NONE,					 // Additional capabilities of the client or server
			NULL);						 // Reserved

		if (FAILED(hr))
		{
			std::cout << "Failed to initialize security. Error code = 0x"
					  << std::hex << hr << std::endl;
			CoUninitialize();
			return false; // Program has failed.
		}
		return true;
	}
};