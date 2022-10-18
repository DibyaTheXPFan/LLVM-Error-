// header fileapi.h begin
/*
WINBASEAPI
DWORD
WINAPI
GetFinalPathNameByHandleW(
    _In_ HANDLE hFile,
    _Out_writes_(cchFilePath) LPWSTR lpszFilePath,
    _In_ DWORD cchFilePath,
    _In_ DWORD dwFlags
    );
*/
/*
DWORD
WINAPI
GetFinalPathNameByHandleW(
    _In_ HANDLE hFile,
    _Out_writes_(cchFilePath) LPWSTR lpszFilePath,
    _In_ DWORD cchFilePath,
    _In_ DWORD dwFlags
);
*/
// header fileapi.h end
//
// GetFinalPathNameByHandleW_Emu Begin
// NtQueryInformationFile begin
// vars begin
//#include <windows.h>
// memcpy
//#include <string.h>








//void *__cdecl memcpy(void *_Dst,
 //                   void const *_Src,
     //                size_t _Size);


typedef unsigned int size_t;
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

typedef struct _OVERLAPPED {
  ULONG_PTR Internal;
  ULONG_PTR InternalHigh;
  union {
    struct {
      DWORD Offset;
      DWORD OffsetHigh;
    } DUMMYSTRUCTNAME;
    PVOID Pointer;
  } DUMMYUNIONNAME;

  HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;

#define DECLARE_HANDLE(name)                                                   \
  struct name##__ {                                                            \
    int unused;                                                                \
  };                                                                           \
  typedef struct name##__ *name

DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE; 

#define INVALID_HANDLE_VALUE ((HANDLE)(LONG_PTR)-1)
#define ERROR_INVALID_PARAMETER 87L // dderror

#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004  
#define OPEN_EXISTING 3
#define FILE_ATTRIBUTE_NORMAL 0x00000080  

typedef enum _FILE_INFORMATION_CLASS_GFPNBHW {
  FileDirectoryInformation = 1
} FILE_INFORMATION_CLASS_GFPNBHW;
typedef struct _UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  PWSTR Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;
typedef LONG NTSTATUS;




    typedef struct _IO_STATUS_BLOCK {
#pragma warning(push)
#pragma warning(disable : 4201) // we'll always use the Microsoft compiler
  union {
    NTSTATUS Status;
    PVOID Pointer;
  } DUMMYUNIONNAME;
#pragma warning(pop)
  ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
typedef enum _OBJECT_INFORMATION_CLASS {
  ObjectBasicInformation = 0,
  ObjectTypeInformation = 2
} OBJECT_INFORMATION_CLASS;

typedef struct _SECURITY_ATTRIBUTES {
  DWORD nLength;
  LPVOID lpSecurityDescriptor;
  BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;
#define VOLUME_NAME_DOS 0x0 // default
#define VOLUME_NAME_GUID 0x1
#define VOLUME_NAME_NT 0x2
#define VOLUME_NAME_NONE 0x4

#define FILE_NAME_NORMALIZED 0x0 // default
#define FILE_NAME_OPENED 0x8


__declspec(dllimport) 
HMODULE 
__stdcall LoadLibraryW(LPCWSTR lpLibFileName);

__declspec(dllimport) int
    __stdcall GetProcAddress( HMODULE hModule, LPCSTR lpProcName);

__declspec(dllimport) HMODULE
    __stdcall
    GetModuleHandleW(LPCWSTR lpModuleName);

__declspec(dllimport) HANDLE
    __stdcall CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess,
            DWORD dwShareMode,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            DWORD dwCreationDisposition,  DWORD dwFlagsAndAttributes,
            HANDLE hTemplateFile);

__declspec(dllimport) BOOL __stdcall DeviceIoControl(HANDLE hDevice, 
	            DWORD dwIoControlCode,
                LPVOID lpInBuffer,
                DWORD nInBufferSize,
                LPVOID lpOutBuffer,
                DWORD nOutBufferSize, LPDWORD lpBytesReturned,
                LPOVERLAPPED lpOverlapped);

__declspec(dllimport) VOID __stdcall SetLastError(DWORD dwErrCode);


__declspec(dllimport) NTSTATUS __stdcall NtQueryObject(
    HANDLE Handle,
    OBJECT_INFORMATION_CLASS ObjectInformationClass,
    PVOID ObjectInformation,
    ULONG ObjectInformationLength, PULONG ReturnLength);

void myMemCpy(void *dest, void *src, size_t n) {
  // Typecast src and dest addresses to (char *)
  char *csrc = (char *)src;
  char *cdest = (char *)dest;

  // Copy contents of src[] to dest[]
  for (unsigned int i = 0; i < n; i++)
    cdest[i] = csrc[i];
}



#define IOCTL_MOUNTMGR_QUERY_POINTS (DWORD) 0x006d0008 
#define IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATH (DWORD) 0x006d0030
	// NtQueryInformationFile_FileNameInformation
BYTE Buffer_NtQueryInformationFile_FileNameInformation_Result[260];
// IOCTL_MOUNTMGR_QUERY_POINTS
BYTE Buffer_MountPointManager_DeviceIoControl_IOCTL_MOUNTMGR_QUERY_POINT_Drive_Result[674];
DWORD DeviceIoControl_lpBytesReturned_IOCTL_MOUNTMGR_QUERY_POINTS;
// IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATH
BYTE Buffer_MountPointManager_DeviceIoControl_IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATH_Drive_Result[674];
DWORD DeviceIoControl_lpBytesReturned_IOCTL_MOUNTMGR_QUERY_DOS_VOLUME_PATH;
// NtQueryObject_ObjectNameInformation
BYTE Buffer_NtQueryObject_ObjectNameInformation_Result[260]; // first 0000 WORD SIZE BYTE WISE // next 0000 WORD size with 0 termination [4] = offset useally plus 8 
WORD Buffer_NtQueryObject_ObjectNameInformation_Size = 0; // Size after offset
ULONG NtQueryObject_Bytes_Returned = 0;
// NtQueryInformationFile_FileNameInformation
WORD Buffer_NtQueryInformationFile_FileNameInformation_Size = 0; // size
// Harddrive String
WORD Distance_To_Harddrive_String = 0;
BYTE Buffer_Harddrive_String[100];
// IOCTL_MOUNTMGR_QUERY_POINTS 
BYTE Buffer_Harddrive_String_IOCTL_MOUNTMGR_QUERY_POINTS[100];

typedef enum _FILE_INFORMATION_CLASS_2 {
	FileDirectoryInformation_2 = 1,
	FileFullDirectoryInformation_2,
	FileBothDirectoryInformation_2,
	FileBasicInformation_2,
	FileStandardInformation_2,
	FileInternalInformation_2,
	FileEaInformation_2,
	FileAccessInformation_2,
	FileNameInformation_2,
	FileRenameInformation_2,
	FileLinkInformation_2,
	FileNamesInformation_2,
	FileDispositionInformation_2,
	FilePositionInformation_2,
	FileFullEaInformation_2,
	FileModeInformation_2,
	FileAlignmentInformation_2,
	FileAllInformation_2,
	FileAllocationInformation_2,
	FileEndOfFileInformation_2,
	FileAlternateNameInformation_2,
	FileStreamInformation_2,
	FilePipeInformation_2,
	FilePipeLocalInformation_2,
	FilePipeRemoteInformation_2,
	FileMailslotQueryInformation_2,
	FileMailslotSetInformation_2,
	FileCompressionInformation_2,
	FileObjectIdInformation_2,
	FileCompletionInformation_2,
	FileMoveClusterInformation_2,
	FileQuotaInformation_2,
	FileReparsePointInformation_2,
	FileNetworkOpenInformation_2,
	FileAttributeTagInformation_2,
	FileTrackingInformation_2,
	FileIdBothDirectoryInformation_2,
	FileIdFullDirectoryInformation_2,
	FileValidDataLengthInformation_2,
	FileShortNameInformation_2,
	FileIoCompletionNotificationInformation_2,
	FileIoStatusBlockRangeInformation_2,
	FileIoPriorityHintInformation_2,
	FileSfioReserveInformation_2,
	FileSfioVolumeInformation_2,
	FileHardLinkInformation_2,
	FileProcessIdsUsingFileInformation,
	FileNormalizedNameInformation,
	FileNetworkPhysicalNameInformation_2,
	FileIdGlobalTxDirectoryInformation_2,
	FileIsRemoteDeviceInformation_2,
	FileAttributeCacheInformation_2,
	FileNumaNodeInformation_2,
	FileStandardLinkInformation_2,
	FileRemoteProtocolInformation_2,
	FileRenameInformationBypassAccessCheck_2,
	FileLinkInformationBypassAccessCheck_2,
	FileVolumeNameInformation_2,
	FileIdInformation_2,
	FileIdExtdDirectoryInformation_2,
	FileReplaceCompletionInformation_2,
	FileHardLinkFullIdInformation_2,
	FileIdExtdBothDirectoryInformation_2,
	FileMaximumInformation
} FILE_INFORMATION_CLASS_2, * PFILE_INFORMATION_CLASS_2;
IO_STATUS_BLOCK NtQueryInformationFile_PIO_STATUS_BLOCK;
// vars end
//NTSYSCALLAPI
NTSTATUS(__stdcall *
	NtQueryInformationFile_GFPNBH)(
		HANDLE                 FileHandle,
		PIO_STATUS_BLOCK       IoStatusBlock,
		PVOID                  FileInformation,
		ULONG                  Length,
 FILE_INFORMATION_CLASS_GFPNBHW FileInformationClass
		) = 0x00000000;

HMODULE hModule_ntdll_NtQueryInformationFile_Switch = 0x00000000;

NTSTATUS
__stdcall 
NtQueryInformationFile_Switch(
	HANDLE                 FileHandle,
	PIO_STATUS_BLOCK       IoStatusBlock,
	PVOID                  FileInformation,
	ULONG                  Length,
	FILE_INFORMATION_CLASS_GFPNBHW FileInformationClass)
{

	if (NtQueryInformationFile_GFPNBH)
	{
    return NtQueryInformationFile_GFPNBH(FileHandle, IoStatusBlock,
                                         FileInformation, Length,
                                         FileInformationClass);
	}


	hModule_ntdll_NtQueryInformationFile_Switch = LoadLibraryW((LPCWSTR) L"ntdll.dll");

	NtQueryInformationFile_GFPNBH =
            (NTSTATUS(__stdcall *)(HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG,
                                   FILE_INFORMATION_CLASS_GFPNBHW))
                GetProcAddress(hModule_ntdll_NtQueryInformationFile_Switch,
                               (LPCSTR) "NtQueryInformationFile");

	if (!hModule_ntdll_NtQueryInformationFile_Switch)
	{
          hModule_ntdll_NtQueryInformationFile_Switch =
              GetModuleHandleW((LPCWSTR)L"ntdll.dll");
          NtQueryInformationFile_GFPNBH =
              (NTSTATUS(__stdcall *)(HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG,
                                     FILE_INFORMATION_CLASS_GFPNBHW))
                  GetProcAddress(hModule_ntdll_NtQueryInformationFile_Switch,
                                 (LPCSTR) "NtQueryInformationFile");
	}

	if (NtQueryInformationFile_GFPNBH)
	{
          return NtQueryInformationFile_GFPNBH(FileHandle, IoStatusBlock,
                                               FileInformation, Length,
                                               FileInformationClass);
	}

	return 0;

}
// NtQueryInformationFile part in GetFinalPathNameByHandleW end
//

typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;




__declspec(noinline) 
DWORD
__stdcall
GetFinalPathNameByHandleW_Emu(
HANDLE file, 
LPWSTR path, 
DWORD count,
DWORD flags) 
{
  typedef enum _OBJECT_INFORMATION_CLASS_2 {
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectAllTypesInformation,
    ObjectHandleInformation
  } OBJECT_INFORMATION_CLASS_2,
      *POBJECT_INFORMATION_CLASS_2;

  WCHAR buffer[sizeof(OBJECT_NAME_INFORMATION) + 260 + 1];
  OBJECT_NAME_INFORMATION *info = (OBJECT_NAME_INFORMATION *)&buffer;
  NTSTATUS status;
  ULONG dummy;

  if (flags & ~(FILE_NAME_OPENED | VOLUME_NAME_GUID | VOLUME_NAME_NONE |
                VOLUME_NAME_NT) ||
      (file == INVALID_HANDLE_VALUE)) {
    SetLastError(ERROR_INVALID_PARAMETER);
    return 0;
  }

  if (flags & VOLUME_NAME_NT) {
    status =
        NtQueryObject(file, (OBJECT_INFORMATION_CLASS)ObjectNameInformation,
                      &buffer, sizeof(buffer) - sizeof(WCHAR), &dummy);
    myMemCpy(path, (void *)&info->Name.Buffer[0], info->Name.Length);

    DWORD NtQueryObject_string_offset_0Termination;
    DWORD *NtQueryObject_string_offset_0Terminationp;
    NtQueryObject_string_offset_0Termination = (DWORD)path;
    NtQueryObject_string_offset_0Termination += info->Name.Length;

    NtQueryObject_string_offset_0Terminationp =
        (DWORD *)NtQueryObject_string_offset_0Termination;
    *NtQueryObject_string_offset_0Terminationp = (WORD)0x0000; // 0 termination

    return (info->Name.Length / 2);
  }

  NtQueryObject(file, (OBJECT_INFORMATION_CLASS)0x00000001,
                Buffer_NtQueryObject_ObjectNameInformation_Result, 0x000000FF,
                &NtQueryObject_Bytes_Returned);
  Buffer_NtQueryObject_ObjectNameInformation_Size =
      (WORD)Buffer_NtQueryObject_ObjectNameInformation_Result[0];

  NtQueryInformationFile_Switch(
      file, &NtQueryInformationFile_PIO_STATUS_BLOCK,
      Buffer_NtQueryInformationFile_FileNameInformation_Result, 0x000000FF,
      (FILE_INFORMATION_CLASS_GFPNBHW)
          FileNameInformation_2); // alernativ 0x00000009 - FileNameInformation
  Buffer_NtQueryInformationFile_FileNameInformation_Size =
      (WORD)Buffer_NtQueryInformationFile_FileNameInformation_Result[0];
  Distance_To_Harddrive_String =
      Buffer_NtQueryObject_ObjectNameInformation_Size -
      Buffer_NtQueryInformationFile_FileNameInformation_Size;
  
  unsigned int Distance_To_Harddrive_String_uint = (unsigned int) Distance_To_Harddrive_String;

  myMemCpy((void *) &Buffer_Harddrive_String[2],
         (void *)&Buffer_NtQueryObject_ObjectNameInformation_Result[8],
    //    (size_t) Distance_To_Harddrive_String);
           Distance_To_Harddrive_String_uint);
       //    10);
  /*
  Buffer_Harddrive_String[0] = (BYTE)Distance_To_Harddrive_String;
  Buffer_Harddrive_String[1] = (BYTE)(Distance_To_Harddrive_String >> 8);

  Buffer_Harddrive_String[Distance_To_Harddrive_String + 1] = (BYTE)0x00;
  Buffer_Harddrive_String[Distance_To_Harddrive_String + 2] = (BYTE)0x00;
  */
  // IOCTL_MOUNTMGR_QUERY_POINTS // Drive number such as C:
 // HANDLE MPM = CreateFileW(L"\\\\.\\MountPointManager", 0,
//                           FILE_SHARE_WRITE || FILE_SHARE_READ, 0,
 //                          OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);



  // nothing of this return error
  SetLastError(ERROR_INVALID_PARAMETER);
  return 0;
  
}
// GetFinalPathNameByHandleW end
//