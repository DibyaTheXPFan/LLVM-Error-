//
// GetThreadId begin
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


#define FAR far
typedef int(FAR __stdcall *FARPROC)();

__declspec(dllimport) HMODULE __stdcall LoadLibraryW(LPCWSTR lpLibFileName);

__declspec(dllimport) HMODULE __stdcall GetModuleHandleW(LPCWSTR lpModuleName);

__declspec(dllimport) FARPROC
    __stdcall GetProcAddress(HMODULE hModule, LPCSTR lpProcName);



ULONG 
NTAPI
RtlNtStatusToDosError(NTSTATUS Status);

DWORD
BaseSetLastNTError_SFIBH(NTSTATUS Status)
{
    DWORD dwErrCode;
    dwErrCode = RtlNtStatusToDosError(Status);
    SetLastError(dwErrCode);
    return dwErrCode;
}

// setfileinformationbyhandle

//#include <minwinbase.h> // this header has FILE_INFO_BY_HANDLE_CLASS
// showing what xp can and not
typedef enum _FILE_INFO_BY_HANDLE_CLASS_02 {
  FileBasicInfo_02,                  // 0  says exits in xp
  FileStandardInfo_02,               // 1 says exits in xp
  FileNameInfo_02,                   // 2 says exits in xp
  FileRenameInfo_02,                 // says 3 exits in xp
  FileDispositionInfo_02,            // 4 says exits in xp
  FileAllocationInfo_02,             // 5 says exits in xp
  FileEndOfFileInfo_02,              // 6 says exits in xp
  FileStreamInfo_02,                 // 7 says exits in xp
  FileCompressionInfo_02,            // 8 says exits in xp
  FileAttributeTagInfo_02,           // 9 says exits in xp
  FileIdBothDirectoryInfo_02,        // 10 says exits in xp
  FileIdBothDirectoryRestartInfo_02, // 11 says exits in xp
//  FileIoPriorityHintInfo_02,      // says vista+
// FileRemoteProtocolInfo, // says win7+
// FileFullDirectoryInfo, // says win8+
// FileFullDirectoryRestartInfo, // says win8+
//#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
// FileStorageInfo,
// FileAlignmentInfo,
// FileIdInfo,
// FileIdExtdDirectoryInfo,
// FileIdExtdDirectoryRestartInfo,
//#endif
//#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1)
// FileDispositionInfoEx,
// FileRenameInfoEx,
//#endif
  FileCaseSensitiveInfo_02,       // unknown
  FileNormalizedNameInfo_02,      // unknown
 MaximumFileInfoByHandleClass_02 // depending on the ifs bigger or smaller also
// count how many options in this enum
} FILE_INFO_BY_HANDLE_CLASS_02,   *PFILE_INFO_BY_HANDLE_CLASS_02;


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

typedef enum _FILE_INFORMATION_CLASS {
  FileDirectoryInformation = 1
} FILE_INFORMATION_CLASS;


NTSTATUS(NTAPI *NtSetInformationFile)
(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation,
 ULONG Length, FILE_INFORMATION_CLASS FileInformationClass) = 0x00000000;

HMODULE hModule_ntdll_NtSetInformationFile_Switch = 0x00000000;
NTSTATUS NTAPI
    NtSetInformationFile_Switch(HANDLE FileHandle,
                                PIO_STATUS_BLOCK IoStatusBlock,
                                PVOID FileInformation, ULONG Length,
                                FILE_INFORMATION_CLASS FileInformationClass) {

  if (NtSetInformationFile) {
    return NtSetInformationFile(FileHandle, IoStatusBlock, FileInformation,
                                Length, FileInformationClass);
  }

  hModule_ntdll_NtSetInformationFile_Switch = LoadLibraryW(L"ntdll.dll");

  NtSetInformationFile = (NTSTATUS(__stdcall *)(HANDLE, PIO_STATUS_BLOCK, PVOID,
                                                ULONG, FILE_INFORMATION_CLASS))
      GetProcAddress(hModule_ntdll_NtSetInformationFile_Switch,
                     "NtSetInformationFile");

  if (!hModule_ntdll_NtSetInformationFile_Switch) {
    hModule_ntdll_NtSetInformationFile_Switch = GetModuleHandleW(L"ntdll.dll");
    NtSetInformationFile = (NTSTATUS(__stdcall *)(
        HANDLE, PIO_STATUS_BLOCK, PVOID, ULONG, FILE_INFORMATION_CLASS))
        GetProcAddress(hModule_ntdll_NtSetInformationFile_Switch,
                       "NtSetInformationFile");
  }

  if (NtSetInformationFile) {
    return NtSetInformationFile(FileHandle, IoStatusBlock, FileInformation,
                                Length, FileInformationClass);
  }

  return FALSE;
}

// BOOL
//(WINAPI*
// SetFileInformationByHandle)(
//    _In_ HANDLE hFile,
//    _In_ FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
//    _In_reads_bytes_(dwBufferSize) LPVOID lpFileInformation,
//    _In_ DWORD dwBufferSize
//) = 0x00000000;
typedef enum _FILE_INFORMATION_CLASS_WDM {
  FileDirectoryInformation_WDM = 1,
  FileFullDirectoryInformation_WDM,            // 2
  FileBothDirectoryInformation_WDM,            // 3
  FileBasicInformation_WDM,                    // 4
  FileStandardInformation_WDM,                 // 5
  FileInternalInformation_WDM,                 // 6
  FileEaInformation_WDM,                       // 7
  FileAccessInformation_WDM,                   // 8
  FileNameInformation_WDM,                     // 9
  FileRenameInformation_WDM,                   // 10
  FileLinkInformation_WDM,                     // 11
  FileNamesInformation_WDM,                    // 12
  FileDispositionInformation_WDM,              // 13
  FilePositionInformation_WDM,                 // 14
  FileFullEaInformation_WDM,                   // 15
  FileModeInformation_WDM,                     // 16
  FileAlignmentInformation_WDM,                // 17
  FileAllInformation_WDM,                      // 18
  FileAllocationInformation_WDM,               // 19
  FileEndOfFileInformation_WDM,                // 20
  FileAlternateNameInformation_WDM,            // 21
  FileStreamInformation_WDM,                   // 22
  FilePipeInformation_WDM,                     // 23
  FilePipeLocalInformation_WDM,                // 24
  FilePipeRemoteInformation_WDM,               // 25
  FileMailslotQueryInformation_WDM,            // 26
  FileMailslotSetInformation_WDM,              // 27
  FileCompressionInformation_WDM,              // 28
  FileObjectIdInformation_WDM,                 // 29
  FileCompletionInformation_WDM,               // 30
  FileMoveClusterInformation_WDM,              // 31
  FileQuotaInformation_WDM,                    // 32
  FileReparsePointInformation_WDM,             // 33
  FileNetworkOpenInformation_WDM,              // 34
  FileAttributeTagInformation_WDM,             // 35
  FileTrackingInformation_WDM,                 // 36
  FileIdBothDirectoryInformation_WDM,          // 37
  FileIdFullDirectoryInformation_WDM,          // 38
  FileValidDataLengthInformation_WDM,          // 39
  FileShortNameInformation_WDM,                // 40
  FileIoCompletionNotificationInformation_WDM, // 41
  FileIoStatusBlockRangeInformation_WDM,       // 42
  FileIoPriorityHintInformation_WDM,           // 43
  FileSfioReserveInformation_WDM,              // 44
  FileSfioVolumeInformation_WDM,               // 45
  FileHardLinkInformation_WDM,                 // 46
  FileProcessIdsUsingFileInformation_WDM,      // 47
  FileNormalizedNameInformation_WDM,           // 48
  FileNetworkPhysicalNameInformation_WDM,      // 49
  FileIdGlobalTxDirectoryInformation_WDM,      // 50
  FileIsRemoteDeviceInformation_WDM,           // 51
  FileUnusedInformation_WDM,                   // 52
  FileNumaNodeInformation_WDM,                 // 53
  FileStandardLinkInformation_WDM,             // 54
  FileRemoteProtocolInformation_WDM,           // 55
                                     //
                                     //  These are special versions of these
                                     //  operations (defined earlier) which can
                                     //  be used by kernel mode drivers only to
                                     //  bypass security access checks for
                                     //  Rename and HardLink operations.  These
                                     //  operations are only recognized by the
                                     //  IOManager, a file system should never
                                     //  receive these.
                                     //

  FileRenameInformationBypassAccessCheck_WDM, // 56
  FileLinkInformationBypassAccessCheck_WDM,   // 57

  //
  // End of special information classes reserved for IOManager.
  //

  FileVolumeNameInformation_WDM,                    // 58
  FileIdInformation_WDM,                            // 59
  FileIdExtdDirectoryInformation_WDM,               // 60
  FileReplaceCompletionInformation_WDM,             // 61
  FileHardLinkFullIdInformation_WDM,                // 62
  FileIdExtdBothDirectoryInformation_WDM,           // 63
  FileDispositionInformationEx_WDM,                 // 64
  FileRenameInformationEx_WDM,                      // 65
  FileRenameInformationExBypassAccessCheck_WDM,     // 66
  FileDesiredStorageClassInformation_WDM,           // 67
  FileStatInformation_WDM,                          // 68
  FileMemoryPartitionInformation_WDM,               // 69
  FileStatLxInformation_WDM,                        // 70
  FileCaseSensitiveInformation_WDM,                 // 71
  FileLinkInformationEx_WDM,                        // 72
  FileLinkInformationExBypassAccessCheck_WDM,       // 73
  FileStorageReserveIdInformation_WDM,              // 74
  FileCaseSensitiveInformationForceAccessCheck_WDM, // 75
  FileKnownFolderInformation_WDM,                   // 76

  FileMaximumInformation_WDM
} FILE_INFORMATION_CLASS_WDM,
    *PFILE_INFORMATION_CLASS_WDM;

HMODULE hModule_ntdll_SetFileInformationByHandle_Switch = 0x00000000;




// typedef enum _FILE_INFO_BY_HANDLE_CLASS_02 {
  // FileBasicInfo_02,                  // 0  says exits in xp
    // FileStandardInfo_02,               // 1 says exits in xp
  //  FileNameInfo_02,                   // 2 says exits in xp
  // FileRenameInfo_02,                 // says 3 exits in xp
  //  FileDispositionInfo_02,            // 4 says exits in xp
  //  FileAllocationInfo_02,             // 5 says exits in xp
  // FileEndOfFileInfo_02,              // 6 says exits in xp
  // FileStreamInfo_02,                 // 7 says exits in xp
 // FileCompressionInfo_02,            // 8 says exits in xp
 // FileAttributeTagInfo_02,           // 9 says exits in xp
 // FileIdBothDirectoryInfo_02,        // 10 says exits in xp
 // FileIdBothDirectoryRestartInfo_02, // 11 says exits in xp
  //  FileIoPriorityHintInfo_02,      // says vista+
  // FileRemoteProtocolInfo, // says win7+
  // FileFullDirectoryInfo, // says win8+
  // FileFullDirectoryRestartInfo, // says win8+
  //#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8)
  // FileStorageInfo,
  // FileAlignmentInfo,
  // FileIdInfo,
  // FileIdExtdDirectoryInfo,
  // FileIdExtdDirectoryRestartInfo,
  //#endif
  //#if (_WIN32_WINNT >= _WIN32_WINNT_WIN10_RS1)
  // FileDispositionInfoEx,
  // FileRenameInfoEx,
  //#endif
//  FileCaseSensitiveInfo_02,       // unknown
//  FileNormalizedNameInfo_02,      // unknown
//  MaximumFileInfoByHandleClass_02 // depending on the ifs bigger or smaller also
  // count how many options in this enum
//} FILE_INFO_BY_HANDLE_CLASS_02,
//    *PFILE_INFO_BY_HANDLE_CLASS_02;
// all that xp has transfered to kernel level numbers
FILE_INFORMATION_CLASS_WDM
ConvertToFileInfo[14] = 
        {FileBasicInformation_WDM,
         FileStandardInformation_WDM,
         FileNameInformation_WDM,
         FileRenameInformation_WDM,
         FileDispositionInformation_WDM,
         FileAllocationInformation_WDM,
         FileEndOfFileInformation_WDM,
         FileStreamInformation_WDM,
         FileCompressionInformation_WDM,
         FileAttributeTagInformation_WDM,
         FileIdBothDirectoryInformation_WDM,
         (FILE_INFORMATION_CLASS_WDM)-1, // FileIdBothDirectoryRestartInfo maybe fault
         FileIoPriorityHintInformation_WDM,
         FileRemoteProtocolInformation_WDM};


// extern "C" __declspec(dllexport)
__declspec(noinline) BOOL WINAPI
    SetFileInformationByHandleX(HANDLE hFile, FILE_INFO_BY_HANDLE_CLASS_02 FileInformationClass,
                                LPVOID lpFileInformation, DWORD dwBufferSize) {
  NTSTATUS Status;
  IO_STATUS_BLOCK IoStatusBlock;
  FILE_INFORMATION_CLASS FileInfoClass;

  FileInfoClass = (FILE_INFORMATION_CLASS)-1; // sets this to invalid

  // Attempt to convert the class
  // convert to ring0 numbers

  // if (FileInformationClass < MaximumFileInfoByHandlesClass)
  if (FileInformationClass <  14) 
  { // coverts for NtSetInformationFile
    FileInfoClass = (FILE_INFORMATION_CLASS)ConvertToFileInfo[FileInformationClass];
  }

  // If wrong, bail out
  if (FileInfoClass == -1) {
    SetLastError(ERROR_INVALID_PARAMETER);
    return FALSE;
  }

  // And set the information
  Status = NtSetInformationFile_Switch(hFile, &IoStatusBlock, lpFileInformation,
                                       dwBufferSize, FileInfoClass);

 
  if (!NT_SUCCESS(Status))
  {
    BaseSetLastNTError_SFIBH(Status);
    return FALSE;
  }

  return TRUE;
}
// setfileinformationbyhandle end