#include "MachineInfo.hxx"

#ifdef _WIN32
#include <Windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#endif

#include <iomanip>
#include <sstream>
#include <string>

namespace universelan {
	MachineInfo::MachineInfo() :
		machine_name{ "" }, user_name{ "" }, macs{}
	{
	}

	static std::string hexStr(const uint8_t* data, int len);
#ifdef _WIN32
	static int RetriveLocalMacAddress(ULONG ulFlags, ULONG ulFamily, unsigned char** pszAddress);
#endif

	std::string MachineInfo::GetLocalMachineName()
	{
#ifdef _WIN32
		if (machine_name.length() == 0) {
			const size_t INFO_BUFFER_SIZE = 32;
			TCHAR  infoBuf[INFO_BUFFER_SIZE];
			DWORD  bufCharCount = INFO_BUFFER_SIZE;

			// Get the computer name.
			if (!GetComputerName(infoBuf, &bufCharCount)) {
				machine_name.assign((const char* const)infoBuf, (const size_t)bufCharCount);
			}
		}
#else
		machine_name = "GetLocalMachineNameNotImplemented";
#endif

		return machine_name;
	}

	std::string MachineInfo::GetLocalUserName()
	{
#ifdef _WIN32
		if (user_name.length() == 0) {
			const size_t INFO_BUFFER_SIZE = 256;
			TCHAR  infoBuf[INFO_BUFFER_SIZE];
			DWORD  bufCharCount = INFO_BUFFER_SIZE;

			// Get the user name.
			if (!GetUserName(infoBuf, &bufCharCount)) {
				user_name.assign((const char* const)infoBuf, (const size_t)bufCharCount);
			}
		}
#else
		user_name = "GetLocalUserNameNotImplemented";
#endif

		return user_name;
	}

	std::vector<std::string> MachineInfo::GetLocalMACs()
	{
		if (macs.size() == 0) {
#ifdef _WIN32
			unsigned char* pszBuff = NULL;
			int nCount = 0;
			int idx = 0;
			int chPos = 0;
			nCount = RetriveLocalMacAddress(GAA_FLAG_INCLUDE_ALL_COMPARTMENTS, AF_UNSPEC, &pszBuff);

			for (idx = 0; idx < nCount; ++idx)
			{
				chPos = MAX_ADAPTER_ADDRESS_LENGTH * idx;
				std::string str(hexStr((pszBuff + chPos), 6));
				if (str != "000000000000") {
					macs.push_back(str);
				}
			}

			HeapFree(GetProcessHeap(), 0x00, pszBuff);
			pszBuff = NULL;
#else
			macs.push_back("12345678abcd");
#endif
		}

		return macs;
	}

	static std::string hexStr(const uint8_t* data, int len)
	{
		std::stringstream ss;
		ss << std::hex;

		for (int i(0); i < len; ++i)
			ss << std::setw(2) << std::setfill('0') << (int)data[i];

		return ss.str();
	}

#ifdef _WIN32
	static int RetriveLocalMacAddress(ULONG ulFlags, ULONG ulFamily, unsigned char** pszAddress)
	{
		PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
		PIP_ADAPTER_ADDRESSES pAddresses = NULL;

		int nAddressCount = 0;
		DWORD dwRetVal = 0;
		ULONG ulBufLen = sizeof(IP_ADAPTER_ADDRESSES);
		HANDLE hHeap = NULL;

		hHeap = GetProcessHeap();
		pAddresses = (PIP_ADAPTER_ADDRESSES)HeapAlloc(hHeap, 0x00, ulBufLen);
		if (pAddresses == NULL) {
			return 0;
		}

		dwRetVal = GetAdaptersAddresses(ulFamily, ulFlags, NULL, pAddresses, &ulBufLen);
		if (dwRetVal == ERROR_BUFFER_OVERFLOW)
		{
			HeapFree(hHeap, 0x00, pAddresses);
			pAddresses = (PIP_ADAPTER_ADDRESSES)HeapAlloc(hHeap, 0x00, ulBufLen);
		}

		if (pAddresses == NULL) {
			return 0;
		}

		dwRetVal = GetAdaptersAddresses(ulFamily, ulFlags, NULL, pAddresses, &ulBufLen);
		if (dwRetVal == NO_ERROR)
		{
			pCurrAddresses = pAddresses;
			while (pCurrAddresses)
			{
				pCurrAddresses = pCurrAddresses->Next;
				++nAddressCount;
			}

			*pszAddress = (unsigned char*)HeapAlloc(hHeap, 0x00, MAX_ADAPTER_ADDRESS_LENGTH * nAddressCount);
			pCurrAddresses = pAddresses;
			nAddressCount = 0;
			while (pCurrAddresses)
			{
				RtlCopyMemory(*pszAddress + (MAX_ADAPTER_ADDRESS_LENGTH * nAddressCount++),
					pCurrAddresses->PhysicalAddress,
					MAX_ADAPTER_ADDRESS_LENGTH);
				pCurrAddresses = pCurrAddresses->Next;
			}
		}

		if (pAddresses) {
			HeapFree(hHeap, 0x00, pAddresses);
			pAddresses = NULL;
		}
		return nAddressCount;
	}
#endif
}
