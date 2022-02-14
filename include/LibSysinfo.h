#include <string>

class LibSysinfoImpl;
class LibSysinfo
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