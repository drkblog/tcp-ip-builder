#include "stdafx.h"
#include "AddressResolver.h"

#include <ws2tcpip.h>

DWORD CAddressResolver::resolve(CString hostname, CString& ips, CString& error)
 {
    const char* format = "Error: %d %s ";
    CString ip;

    WSADATA wsaData;
    int iResult;

    DWORD dwRetval;

    struct addrinfo* result = NULL;
    struct addrinfo* ptr = NULL;
    struct addrinfo hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        error.Format(format, iResult, "Failed to initialize WSAStartup");
        return iResult;
    }

    //--------------------------------
    // Setup the hints address info structure
    // which is passed to the getaddrinfo() function
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    //--------------------------------
    // Call getaddrinfo(). If the call succeeds,
    // the result variable will hold a linked list
    // of addrinfo structures containing response
    // information
    dwRetval = getaddrinfo(hostname, "", &hints, &result);
    if (dwRetval != 0) {
        error.Format(format, dwRetval, "Failed getaddrinfo");
        WSACleanup();
        return dwRetval;
    }

    // Retrieve each address and print out the hex bytes
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        switch (ptr->ai_family) {
        case AF_UNSPEC:
            ip = "Unspecified\n";
            break;
        case AF_INET:
            inAddrToString((LPSOCKADDR)ptr->ai_addr, ptr->ai_addrlen, ip);
            break;
        case AF_INET6:
            inAddrToString((LPSOCKADDR)ptr->ai_addr, ptr->ai_addrlen, ip);
            break;
        case AF_NETBIOS:
            ip.Format("AF_NETBIOS (NetBIOS)");
            break;
        default:
            ip.Format("Other %ld", ptr->ai_family);
            break;
        }
        ips.Append(ip);
        ips.Append(" - (");
        ips.Append(ptr->ai_canonname);
        ips.Append(")\r\n");
    }

    freeaddrinfo(result);
    WSACleanup();

    return 0;
}

#define BUFFER_LENGHT 46

DWORD CAddressResolver::inAddrToString(LPSOCKADDR sockaddr_ip, DWORD address_length, CString& ip) {
    DWORD dwRetval, ipbufferlength = BUFFER_LENGHT;
    WCHAR wideAddress[BUFFER_LENGHT];

    dwRetval = WSAAddressToStringW(sockaddr_ip, address_length, NULL, wideAddress, &ipbufferlength);
    if (dwRetval == 0) {
        CStringA string = CStringA(wideAddress);
        ip = string;
    }

    return dwRetval;
}