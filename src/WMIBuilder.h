#pragma once
#define _WIN32_DCOM
#include <iostream>
#include <windows.h>
#include <wbemidl.h>
#include <vector>
#include <comdef.h>
#include <algorithm>

#pragma comment(lib, "wbemuuid.lib")

class WMIBuilder
{
public:
	IWbemServices* GetService()
	{
		return pSvc;
	}

	std::vector<std::vector<std::string>> ExecWQL(const std::vector<std::string>& cols, const std::string& table)
	{
		std::string query = std::move(std::string("SELECT * FROM ").append(table));
		std::vector<std::vector<std::string>> result;

		// Use the IWbemServices pointer to make requests of WMI
		IEnumWbemClassObject* pEnumerator = NULL;
		hr = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t(query.c_str()),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (FAILED(hr))
		{
			std::cout << "Query for operating system name failed."
					  << " Error code = 0x"
					  << std::hex << hr << std::endl;
			return result;
		}

		// Get the data from the query
		IWbemClassObject* pclsObj = NULL;
		ULONG uReturn = 0;

		while (pEnumerator)
		{
			HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
				&pclsObj, &uReturn);

			if (0 == uReturn)
			{
				break;
			}

			VARIANT vtProp;
			result.push_back({});

			// Get the value of the Name property
			std::for_each(cols.begin(), cols.end(), [&](const std::string& col) {
				hr = pclsObj->Get(bstr_t(col.c_str()), 0, &vtProp, 0, 0);
				result.back().push_back(std::string(bstr_t(vtProp.bstrVal)));
				std::cout << "ExecWQL - " << col.c_str() << " : " << result.back().back() << std::endl;
			});
			VariantClear(&vtProp);

			pclsObj->Release();
		}
		return result;
	}

	//�ͷ����д򿪵� COM �ӿڡ�
	//�������סҪ������������Ҫ�ӿ���IWbemServices��IWbemLocator��
	//����CoUninitialize��
	//������ COM Ӧ�ó���һ������������Ӧ�ó������ʱ����CoUninitialize ��
	bool Initialize()
	{
		if (!InitializeWMI() || !ConnectWMI() || !SetLevels())
			return false;
		return true;
	}

	bool Release()
	{
		pSvc->Release();
		pLoc->Release();
		return true; // Program successfully completed.
	}

private:
	HRESULT hr;
	IWbemLocator* pLoc = 0;
	IWbemServices* pSvc = 0;

	// ͨ������CoCreateInstance��ʼ��IWbemLocator�ӿ�
	// WMI ��Ҫ������IWbemLocator�ϵ���CoCreateInstanceʱִ���κ���������
	bool InitializeWMI()
	{

		hr = CoCreateInstance(CLSID_WbemLocator, 0,
			CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);

		if (FAILED(hr))
		{
			std::cout << "Failed to create IWbemLocator object. Err code = 0x"
					  << std::hex << hr << std::endl;
			CoUninitialize();
			return false; // Program has failed.
		}
		return true;
	}

	// ͨ������IWbemLocator::ConnectServer�������ӵ� WMI
	// ConnectServer�����������ص�IWbemServices�ӿڣ��ýӿ����ڷ����ڶ�ConnectServer�ĵ�����ָ���ı��ػ�Զ�� WMI �����ռ�
	bool ConnectWMI()
	{

		// Connect to the root\default namespace with the current user.
		hr = pLoc->ConnectServer(
			BSTR(L"ROOT\\CIMV2"), // namespace
			NULL,				  // User name
			NULL,				  // User password
			0,					  // Locale
			NULL,				  // Security flags
			0,					  // Authority
			0,					  // Context object
			&pSvc);				  // IWbemServices proxy


		if (FAILED(hr))
		{
			std::cout << "Could not connect. Error code = 0x"
					  << std::hex << hr << std::endl;
			pLoc->Release();
			CoUninitialize();
			return false; // Program has failed.
		}

		std::cout << "Connected to WMI" << std::endl;
		return true;
	}

	// ͨ������CoSetProxyBlanket��IWbemServices���������ð�ȫ����
	bool SetLevels()
	{
		// Set the proxy so that impersonation of the client occurs.
		hr = CoSetProxyBlanket(pSvc,
			RPC_C_AUTHN_WINNT,
			RPC_C_AUTHZ_NONE,
			NULL,
			RPC_C_AUTHN_LEVEL_CALL,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			EOAC_NONE);

		if (FAILED(hr))
		{
			std::cout << "Could not set proxy blanket. Error code = 0x"
					  << std::hex << hr << std::endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return false; // Program has failed.
		}
		return true;
	}
};