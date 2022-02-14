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

	// ͨ������CoInitializeEx����ʼ�� COM
	// ����CoInitializeEx������ COM �ӿڵı�׼���̡���ˣ�WMI ����Ҫ���ڵ���CoInitializeExʱ�����κ��������̡��й���ϸ��Ϣ�������COM��
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

	// ͨ������CoInitializeSecurity�ӿ�����ͨ�� COM ��ȫ����
	// CoInitializeSecurity��Ϊ�������� COM �ӿ�ʱ������õı�׼���������ҪΪ�������̵������֤��ģ��������֤��������Ĭ�ϰ�ȫ���ã������CoInitializeSecurity ���й���ϸ��Ϣ����������ÿͻ���Ӧ�ó�����̰�ȫ�ԡ����Ҫ���û�����ض�����İ�ȫ�ԣ���������CoSetProxyBlanket�������޷����������֤��ģ��������֤�����Ĭ�ϰ�ȫ���õ���һ������������ʱ�������������û���� COM ��ȫ��ʱ����ʹ��CoSetProxyBlanket
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