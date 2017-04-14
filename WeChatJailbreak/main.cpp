//
// Modified by Caily on 14/4/2017.
//


#include <Windows.h>

#include "NtSupport.h"

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
	DWORD dwCurrentProcessId = *((DWORD*)lParam);
	DWORD dwProcessId = 0;

	GetWindowThreadProcessId(hWnd, &dwProcessId);

	if (dwProcessId == dwCurrentProcessId && NULL == GetParent(hWnd)) {
		*((HWND*)lParam) = hWnd;
		return false;
	}

	return true;
}

HWND GetMainWindow() {
	DWORD PID = GetCurrentProcessId();

	if (!EnumWindows(EnumWindowsProc, (LPARAM)&PID)) {
		return (HWND)PID;
	}

	return NULL;
}

bool GetPrivileges() {
	// 取得当前进程的[Token](标识)句柄
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;

	// 确保能关闭句柄
	HANDLE handle(hToken);

	// 取得关闭系统的[LUID](本地唯一的标识符)值
	TOKEN_PRIVILEGES stTokenPrivilege;
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &stTokenPrivilege.Privileges[0].Luid))
		return false;

	// 设置特权数组的元素个数
	stTokenPrivilege.PrivilegeCount = 1;

	// 设置[LUID]的属性值
	stTokenPrivilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// 为当前进程取得DEBUG权限
	if (!AdjustTokenPrivileges(hToken, FALSE, &stTokenPrivilege, 0, NULL, NULL))
		return false;

	return true;
}

extern "C" __declspec(dllexport) BOOL ClearWeChatMutex(DWORD PID) {
	CNtSupport nt(SYSTEM_INFORMATION_CLASS::SystemHandleInformation);
	return nt.QueryAndCloseHandle(PID, L"Mutant", L"_WeChat_App_Instance_Identity_Mutex_Name");
}


extern "C" __declspec(dllexport) BOOL GetWeChatID(DWORD PID) {
	CNtSupport nt(SYSTEM_INFORMATION_CLASS::SystemHandleInformation);
	LPWSTR buffer = nt.GetMutantByPartWords(PID, L"_WeChat_Win_User_Identity_Mutex_Name");

	if (true == OpenClipboard(GetMainWindow())) {

		//清空剪贴板  
		EmptyClipboard();

		//将选中的字符串放到全局内存中  
		HGLOBAL hGol = GlobalAlloc(GMEM_MOVEABLE, 2014 * sizeof(WCHAR));

		//锁定此时分配得到的全局内存，防止数据被更改  
		LPWSTR lpStrcpy = (LPWSTR)GlobalLock(hGol);
		memcpy(lpStrcpy, buffer, 100 * sizeof(WCHAR));

		//解锁，设置剪贴板内容  
		GlobalUnlock(hGol);
		SetClipboardData(CF_UNICODETEXT, hGol);

		//关闭剪贴板  
		CloseClipboard();
	}

	return true;
}

BOOL WINAPI DllMain(
	IN HANDLE hModule,
	IN DWORD ul_reasion_for_call,
	IN LPVOID lpReserved) {
	GetPrivileges();

	switch (ul_reasion_for_call)
	{
		/** the dll file has been loaded by other executable file */
		case DLL_PROCESS_ATTACH:
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;

		/** the dll file has been unloaded by other executable file */
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}



