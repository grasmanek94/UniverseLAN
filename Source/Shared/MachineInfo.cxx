#include "MachineInfo.hxx"

#ifdef _WIN32
#include <Windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#else
#include <unistd.h>
#endif

#include <cstdint>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>

namespace universelan {
#ifdef _WIN32
	namespace {
#pragma data_seg(".universelanclientapimultiprocessdebugcounter") 
		volatile DWORD processes[16] = {
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		};

		// From testing it looks like this is fine/works... but I'm not sure
		std::mutex mtx_processes;
#pragma data_seg()
#pragma comment(linker, "/section:.universelanclientapimultiprocessdebugcounter,rws")
	}
#endif

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

	std::size_t MachineInfo::GetProcessID() {
		std::size_t process_id = 0;

#ifdef _WIN32
		process_id = (std::size_t)GetCurrentProcessId();
#else
		process_id = (std::size_t)::getpid();
#endif

		return process_id;
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


	static int IsPidRunning(DWORD pid)
	{
		HANDLE hProcess;
		DWORD exitCode;

		//Special case for PID 0 System Idle Process
		if (pid == 0) {
			return 1;
		}

		//skip testing bogus PIDs
		if (pid < 0) {
			return 0;
		}

		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
		if (NULL == hProcess) {
			//invalid parameter means PID isn't in the system
			if (GetLastError() == ERROR_INVALID_PARAMETER) {
				return 0;
			}

			//some other error with OpenProcess
			return -1;
		}

		if (GetExitCodeProcess(hProcess, &exitCode)) {
			CloseHandle(hProcess);
			return (exitCode == STILL_ACTIVE);
		}

		//error in GetExitCodeProcess()
		CloseHandle(hProcess);
		return -1;
	}
#endif

	int MachineInfo::GetDebugID() {
#ifdef _WIN32
		std::scoped_lock<std::mutex> lock{ mtx_processes };

		for (int i = 0; i < 16; ++i) {
			if (processes[i] == GetCurrentProcessId()) {
				return i;
			}
	}

		for (int i = 0; i < 16; ++i) {
			if (processes[i] == 0 || !IsPidRunning(processes[i])) {
				processes[i] = GetCurrentProcessId();
				return i;
			}
		}		
#endif
		return -1;
	}
}
