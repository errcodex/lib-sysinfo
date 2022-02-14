#include <string>
#include <memory>

class COMBuilder;
class WMIBuilder;

class LibSysinfoImpl
{

public:
	LibSysinfoImpl();
	~LibSysinfoImpl();

	bool Initialize();
	bool Release();
	std::string GetOS();

private:
	std::shared_ptr<COMBuilder> com;
	std::shared_ptr<WMIBuilder> wmi;
};