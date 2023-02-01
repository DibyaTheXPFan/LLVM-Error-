//#include <winternl.h>
//#include <windows.h>

#define far
typedef void *PVOID;
typedef unsigned short USHORT;
typedef unsigned short WCHAR;
typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR;
typedef unsigned short WORD;
typedef void *HANDLE;
typedef unsigned char BYTE;
typedef unsigned long ULONG;
typedef unsigned long DWORD;
typedef long LONG;
typedef unsigned long ULONG_PTR, *PULONG_PTR;
typedef long LONG_PTR, *PLONG_PTR;
typedef WCHAR *LPCWSTR, *PCWSTR;
typedef void far *LPVOID;
typedef ULONG *PULONG;
typedef int BOOL;
typedef char CHAR;
typedef CHAR *NPSTR, *LPSTR, *PSTR;
#define LPCSTR LPSTR
typedef DWORD far *LPDWORD;
#define VOID void
#define ThreadBasicInformation 0x00

typedef LONG NTSTATUS;

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)

#define WINAPI __stdcall
#define NULL 0
typedef enum _THREADINFOCLASS { ThreadIsIoPending = 16 } THREADINFOCLASS;

#define DECLARE_HANDLE(name)                                                   \
  struct name##__ {                                                            \
    int unused;                                                                \
  };                                                                           \
  typedef struct name##__ *name
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define ERROR_INVALID_PARAMETER 87L // dderror

#define NTAPI __stdcall
#define WINAPI __stdcall

#define DECLSPEC_IMPORT __declspec(dllimport)
#define WINBASEAPI DECLSPEC_IMPORT

WINBASEAPI
VOID WINAPI SetLastError(DWORD dwErrCode);

typedef ULONG_PTR SIZE_T, *PSIZE_T;

#define FAR far
typedef int(FAR __stdcall *FARPROC)();

__declspec(dllimport) HMODULE __stdcall LoadLibraryW(LPCWSTR lpLibFileName);

__declspec(dllimport) HMODULE __stdcall GetModuleHandleW(LPCWSTR lpModuleName);

__declspec(dllimport) FARPROC
    __stdcall GetProcAddress(HMODULE hModule, LPCSTR lpProcName);

ULONG
NTAPI
RtlNtStatusToDosError(NTSTATUS Status);


// psapi
// const wchar_t kPsapiDllName[] = L"psapi.dll";
typedef struct _PROCESS_MEMORY_COUNTERS_EMU {
  DWORD cb;
  DWORD PageFaultCount;
  SIZE_T PeakWorkingSetSize;
  SIZE_T WorkingSetSize;
  SIZE_T QuotaPeakPagedPoolUsage;
  SIZE_T QuotaPagedPoolUsage;
  SIZE_T QuotaPeakNonPagedPoolUsage;
  SIZE_T QuotaNonPagedPoolUsage;
  SIZE_T PagefileUsage;
  SIZE_T PeakPagefileUsage;
} PROCESS_MEMORY_COUNTERS_EMU, *PPROCESS_MEMORY_COUNTERS_EMU;

// also named K32EnumProcessModules
BOOL(WINAPI *EnumProcessModules_var)
(HANDLE hProcess, HMODULE *lphModule, DWORD cb,
 LPDWORD lpcbNeeded) = 0x00000000;

HMODULE hModule_ntdll_EnumProcessModules_Switch = 0x00000000;

__declspec(noinline)
BOOL
WINAPI
EnumProcessModulesX(HANDLE hProcess, HMODULE *lphModule, DWORD cb,
                        LPDWORD lpcbNeeded) {

  if (EnumProcessModules_var) {
    return EnumProcessModules_var(hProcess, lphModule, cb, lpcbNeeded);
  }

  hModule_ntdll_EnumProcessModules_Switch = LoadLibraryW(L"psapi.dll");

  EnumProcessModules_var =
      (BOOL(__stdcall *)(HANDLE, HMODULE *, DWORD, LPDWORD))GetProcAddress(
          hModule_ntdll_EnumProcessModules_Switch, "EnumProcessModules");

  if (!hModule_ntdll_EnumProcessModules_Switch) {
    hModule_ntdll_EnumProcessModules_Switch = GetModuleHandleW(L"psapi.dll");
    EnumProcessModules_var =
        (BOOL(__stdcall *)(HANDLE, HMODULE *, DWORD, LPDWORD))GetProcAddress(
            hModule_ntdll_EnumProcessModules_Switch, "EnumProcessModules");
  }

  if (EnumProcessModules_var) {
    return EnumProcessModules_var(hProcess, lphModule, cb, lpcbNeeded);
  }

  if (!EnumProcessModules_var) // only for extra functionality
  {
    // The function could not be loaded!
    memset(lphModule, 0, cb);
    return FALSE;
  }

  return FALSE;
}

// GetProcessMemoryInfo must be dynamically loaded to support Windows XP.
BOOL(WINAPI *GetProcessMemoryInfo_var)
(HANDLE Process, PPROCESS_MEMORY_COUNTERS_EMU ppsmemCounters,
 DWORD cb) = 0x00000000;

HMODULE hModule_ntdll_GetProcessMemoryInfo_Switch = 0x00000000;
// Beware of races if called concurrently from multiple threads.
__declspec(noinline)
BOOL 
WINAPI
GetProcessMemoryInfoX(HANDLE Process,
                          PPROCESS_MEMORY_COUNTERS_EMU ppsmemCounters,
                          DWORD cb) {


  if (GetProcessMemoryInfo_var)
  {
    return GetProcessMemoryInfo_var(Process, ppsmemCounters, cb);
  }

  hModule_ntdll_GetProcessMemoryInfo_Switch = LoadLibraryW(L"psapi.dll");

  GetProcessMemoryInfo_var =
      (BOOL(__stdcall *)(HANDLE, PPROCESS_MEMORY_COUNTERS_EMU, DWORD))
          GetProcAddress(hModule_ntdll_GetProcessMemoryInfo_Switch,
                         "GetProcessMemoryInfo");

  if (!hModule_ntdll_GetProcessMemoryInfo_Switch) {
    hModule_ntdll_GetProcessMemoryInfo_Switch = GetModuleHandleW(L"psapi.dll");
    GetProcessMemoryInfo_var =
        (BOOL(__stdcall *)(HANDLE, PPROCESS_MEMORY_COUNTERS_EMU, DWORD))
            GetProcAddress(hModule_ntdll_GetProcessMemoryInfo_Switch,
                           "GetProcessMemoryInfo");
  }

  if (GetProcessMemoryInfo_var) {
    return GetProcessMemoryInfo_var(Process, ppsmemCounters, cb);
  }

  if (!GetProcessMemoryInfo_var) // only for extra functionality
  {
    // The function could not be loaded!
    memset(ppsmemCounters, 0, cb);
    return FALSE;
  }

  return FALSE;
}
// psapi end