#pragma once
class CAddressResolver
{
private:
	DWORD CAddressResolver::inAddrToString(LPSOCKADDR sockaddr_ip, DWORD address_length, CString& ip);
public:
	DWORD resolve(CString hostname, CString& ips, CString& error);
};

