//#include <winternl.h>
//#include <windows.h>
//#include <winnt.h>

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
typedef USHORT *PUSHORT;
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
#define near

typedef int(FAR __stdcall *FARPROC)();
typedef DWORD near *PDWORD;




typedef enum _LOGICAL_PROCESSOR_RELATIONSHIP {
  RelationProcessorCore,
  RelationNumaNode,
  RelationCache,
  RelationProcessorPackage,
  RelationGroup,
  RelationAll = 0xffff
} LOGICAL_PROCESSOR_RELATIONSHIP;

typedef enum _PROCESSOR_CACHE_TYPE {
  CacheUnified,
  CacheInstruction,
  CacheData,
  CacheTrace
} PROCESSOR_CACHE_TYPE;

typedef struct _CACHE_DESCRIPTOR {
  BYTE Level;
  BYTE Associativity;
  WORD LineSize;
  DWORD Size;
  PROCESSOR_CACHE_TYPE Type;
} CACHE_DESCRIPTOR, *PCACHE_DESCRIPTOR;

typedef unsigned __int64 ULONGLONG;

typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION {
  ULONG_PTR ProcessorMask;
  LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
  union {
    struct {
      BYTE Flags;
    } ProcessorCore;
    struct {
      DWORD NodeNumber;
    } NumaNode;
    CACHE_DESCRIPTOR Cache;
    ULONGLONG Reserved[2];
  } DUMMYUNIONNAME;
} SYSTEM_LOGICAL_PROCESSOR_INFORMATION, *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION;



typedef ULONG_PTR KAFFINITY;
typedef char CCHAR;

#define ANYSIZE_ARRAY 1 

typedef struct _GROUP_AFFINITY {
  KAFFINITY Mask;
  WORD Group;
  WORD Reserved[3];
} GROUP_AFFINITY, *PGROUP_AFFINITY;

typedef struct _PROCESSOR_RELATIONSHIP {
  BYTE Flags;
  BYTE EfficiencyClass;
  BYTE Reserved[20];
  WORD GroupCount;
  GROUP_AFFINITY GroupMask[ANYSIZE_ARRAY];
} PROCESSOR_RELATIONSHIP, *PPROCESSOR_RELATIONSHIP;


typedef struct _NUMA_NODE_RELATIONSHIP {
  DWORD NodeNumber;
  BYTE Reserved[20];
  GROUP_AFFINITY GroupMask;
} NUMA_NODE_RELATIONSHIP, *PNUMA_NODE_RELATIONSHIP;


typedef struct _CACHE_RELATIONSHIP {
  BYTE Level;
  BYTE Associativity;
  WORD LineSize;
  DWORD CacheSize;
  PROCESSOR_CACHE_TYPE Type;
  BYTE Reserved[20];
  GROUP_AFFINITY GroupMask;
} CACHE_RELATIONSHIP, *PCACHE_RELATIONSHIP;

typedef struct _PROCESSOR_GROUP_INFO {
  BYTE MaximumProcessorCount;
  BYTE ActiveProcessorCount;
  BYTE Reserved[38];
  KAFFINITY ActiveProcessorMask;
} PROCESSOR_GROUP_INFO, *PPROCESSOR_GROUP_INFO;

typedef struct _GROUP_RELATIONSHIP {
  WORD MaximumGroupCount;
  WORD ActiveGroupCount;
  BYTE Reserved[20];
  PROCESSOR_GROUP_INFO GroupInfo[ANYSIZE_ARRAY];
} GROUP_RELATIONSHIP, *PGROUP_RELATIONSHIP;




typedef enum _SYSTEM_INFORMATION_CLASS {
  SystemBasicInformation = 0,
  SystemPerformanceInformation = 2,
  SystemTimeOfDayInformation = 3,
  SystemProcessInformation = 5,
  SystemProcessorPerformanceInformation = 8,
  SystemInterruptInformation = 23,
  SystemExceptionInformation = 33,
  SystemRegistryQuotaInformation = 37,
  SystemLookasideInformation = 45,
  SystemCodeIntegrityInformation = 103,
  SystemPolicyInformation = 134,
} SYSTEM_INFORMATION_CLASS;


typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX {
  LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
  DWORD Size;
  union {
    PROCESSOR_RELATIONSHIP Processor;
    NUMA_NODE_RELATIONSHIP NumaNode;
    CACHE_RELATIONSHIP Cache;
    GROUP_RELATIONSHIP Group;
  } DUMMYUNIONNAME;
};


typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX,
    *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX;

WINBASEAPI
BOOL WINAPI GetLogicalProcessorInformation(
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION Buffer, PDWORD ReturnedLength);

typedef unsigned int UINT_PTR, *PUINT_PTR;

WINBASEAPI
BOOL WINAPI IsBadWritePtr(LPVOID lp, UINT_PTR ucb);

NTSTATUS 
NTAPI 
NtQuerySystemInformation(
SYSTEM_INFORMATION_CLASS SystemInformationClass,
PVOID SystemInformation, 
ULONG SystemInformationLength,
PULONG ReturnLength);

// GetLogicalProcessorInformationEx_Emu function begin
//
// part 1 GetLogicalProcessorInformation vars begin
// this function calls internal NtQuerySystemInformation with 0x49 =
// SystemLogicalProcessorInformation the SYSTEM_LOGICAL_PROCESSOR_INFORMATION
// has entrys 8 cores had 37 s0 we do 1120 entrys 37/8 * 256 cores
BYTE buffer_GetLogicalProcessorInformation_01[(
    sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) * 1120)];
ULONG returnLength_GetLogicalProcessorInformation_01 =
    0;                                         // len returned and given
ULONG GetLogicalProcessorInformation_MULT = 0; // multiplyer
PSYSTEM_LOGICAL_PROCESSOR_INFORMATION GetLogicalProcessorInformation_OFFSET = 0;
DWORD number_of_numaNodeCount_GetLogicalProcessorInformation_direct_var =
    0;                                               // ->NumaNode.NodeNumber;
DWORD RelationProcessorCore_ProcessorCore_Flags = 0; // ->ProcessorCore.Flags
DWORD number_of_logicalProcessorCount_GetLogicalProcessorInformation =
    0; // Number of logical processors
DWORD number_of_numaNodeCount_GetLogicalProcessorInformation =
    0; // Number of NUMA nodes
DWORD number_of_processorCoreCount_GetLogicalProcessorInformation =
    0; // Number of processor cores
DWORD number_of_processorL1CacheCount_GetLogicalProcessorInformation =
    0; // Number of processor L3 caches
DWORD number_of_processorL2CacheCount_GetLogicalProcessorInformation =
    0; // Number of processor L2 caches
DWORD number_of_processorL3CacheCount_GetLogicalProcessorInformation =
    0; // Number of processor L3 caches
DWORD number_of_processorPackageCount_GetLogicalProcessorInformation =
    0; // Number of physical processor packages
// Helper function to count set bits in the processor mask.
DWORD CountSetBits(ULONG_PTR bitMask) {
  DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
  DWORD bitSetCount = 0;
  ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
  DWORD i;

  for (i = 0; i <= LSHIFT; ++i) {
    bitSetCount += ((bitMask & bitTest) ? 1 : 0);
    bitTest /= 2;
  }

  return bitSetCount;
}
// part 1 GetLogicalProcessorInformation vars end
//
// part 2 SYSTEM_PROCESSOR_INFORMATION for GetLogicalProcessorInformationEx emu
// function vars begin
ULONG
    ReturnLength_GetLogicalProcessorInformationEx_SYSTEM_PROCESSOR_INFORMATION_01 =
        0;
struct _SYSTEM_PROCESSOR_INFORMATION_GetLogicalProcessorInformationEx {
  USHORT ProcessorArchitecture; // ushort is 2 byes
  USHORT ProcessorLevel;
  USHORT ProcessorRevision;
  //#if (NTDDI_VERSION < NTDDI_WIN8)
  USHORT Reserved; // smaller then win8 reserved // win8 + Reserved is =
                   // MaximumProcessors
                   //#else
  //	USHORT MaximumProcessors; // win8 and greater this - held same value as
  //SYSTEM_BASIC_INFORMATION - CCHAR NumberOfProcessors;
  //#endif
  ULONG ProcessorFeatureBits;
} SYSTEM_PROCESSOR_INFORMATION_GetLogicalProcessorInformationEx,
    *PSYSTEM_PROCESSOR_INFORMATION_GetLogicalProcessorInformationEx;
// part 2 SYSTEM_PROCESSOR_INFORMATION for GetLogicalProcessorInformationEx emu
// function vars end
//
// part 3 vars begin
unsigned int i_RelationProcessorCore =
    0; // used for main counter in processorcore need more access - aka global
// part 3 vars end
//
// part 3 SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx emu function
// vars begin
struct _SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01 {
  ULONG Reserved;
  ULONG TimerResolution;
  ULONG PageSize;
  ULONG NumberOfPhysicalPages;
  ULONG LowestPhysicalPageNumber;
  ULONG HighestPhysicalPageNumber;
  ULONG AllocationGranularity;
  ULONG MinimumUserModeAddress;
  ULONG MaximumUserModeAddress;
  KAFFINITY ActiveProcessorsAffinityMask;
  CCHAR NumberOfProcessors;
} SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01,
    *PSYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01;
ULONG ReturnLengthGetLogicalProcessorInformationEx_SYSTEM_BASIC_INFORMATION_01 =
    0;
// part 3 SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx emu function
// vars end
//
// GetLogicalProcessorInformationEx_Emu function
BOOL WINAPI GetLogicalProcessorInformationExX(
    LOGICAL_PROCESSOR_RELATIONSHIP RelationshipType,
    // PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer,
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer, PDWORD ReturnedLength) {
  //
  // part 1 (function) GetLogicalProcessorInformationEx Emu function begin
  // make sure returnLength_GetLogicalProcessorInformation_0 is 0
  returnLength_GetLogicalProcessorInformation_01 = 0x00000000;
  // First call is to figure out the lenght inside the needed buffer
  GetLogicalProcessorInformation(
      (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)
          buffer_GetLogicalProcessorInformation_01,
      &returnLength_GetLogicalProcessorInformation_01);
  // the next call should not fail
  if (GetLogicalProcessorInformation(
          (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)
              buffer_GetLogicalProcessorInformation_01,
          &returnLength_GetLogicalProcessorInformation_01)) {
    GetLogicalProcessorInformation_MULT =
        (returnLength_GetLogicalProcessorInformation_01 /
         (sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION)));
    // init 0
    number_of_numaNodeCount_GetLogicalProcessorInformation = 0;
    number_of_processorCoreCount_GetLogicalProcessorInformation = 0;
    number_of_logicalProcessorCount_GetLogicalProcessorInformation = 0;
    number_of_processorL1CacheCount_GetLogicalProcessorInformation = 0;
    number_of_processorL2CacheCount_GetLogicalProcessorInformation = 0;
    number_of_processorL3CacheCount_GetLogicalProcessorInformation = 0;
    number_of_processorPackageCount_GetLogicalProcessorInformation = 0;

    for (ULONG i = 0; i < GetLogicalProcessorInformation_MULT; i++) {
      GetLogicalProcessorInformation_OFFSET =
          (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)(
              (i * (sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION))) +
              buffer_GetLogicalProcessorInformation_01);

      // GetLogicalProcessorInformation_OFFSET->Relationship;

      switch (GetLogicalProcessorInformation_OFFSET->Relationship) {
      case RelationNumaNode:
        // Non-NUMA systems report a single record of this type.
        number_of_numaNodeCount_GetLogicalProcessorInformation++;
        number_of_numaNodeCount_GetLogicalProcessorInformation_direct_var =
           // GetLogicalProcessorInformation_OFFSET->NumaNode.NodeNumber;
            GetLogicalProcessorInformation_OFFSET->DUMMYUNIONNAME.NumaNode.NodeNumber;
      break;


      case RelationProcessorCore:
        number_of_processorCoreCount_GetLogicalProcessorInformation++;

        // tells if hyperthreaded // virtual cores // Hyperthreading // SMT
        RelationProcessorCore_ProcessorCore_Flags =
           // GetLogicalProcessorInformation_OFFSET->ProcessorCore.Flags;
            GetLogicalProcessorInformation_OFFSET->DUMMYUNIONNAME.ProcessorCore.Flags;
        // A hyperthreaded core supplies more than one logical processor.
        number_of_logicalProcessorCount_GetLogicalProcessorInformation +=
            CountSetBits(GetLogicalProcessorInformation_OFFSET->ProcessorMask);
        break;

      case RelationCache:
        // this function  CACHE_DESCRIPTOR
        // Ex version     CACHE_RELATIONSHIP
        // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each
        // cache.
       // if (GetLogicalProcessorInformation_OFFSET->Cache.Level == (BYTE)1) {
        if (GetLogicalProcessorInformation_OFFSET->DUMMYUNIONNAME.Cache.Level ==
            (BYTE)1) {
          number_of_processorL1CacheCount_GetLogicalProcessorInformation++;
        } else if (GetLogicalProcessorInformation_OFFSET->DUMMYUNIONNAME.Cache
                       .Level ==
                   (BYTE)2) {
          number_of_processorL2CacheCount_GetLogicalProcessorInformation++;
        } else if (GetLogicalProcessorInformation_OFFSET->DUMMYUNIONNAME.Cache
                       .Level ==
                   (BYTE)3) {
          number_of_processorL3CacheCount_GetLogicalProcessorInformation++;
        }
        break;

      case RelationProcessorPackage:
        // Logical processors share a physical package.
        number_of_processorPackageCount_GetLogicalProcessorInformation++;
        break;

      default:
        // unknown relation - did not hit even in win10
        break;
      }

      if (i > 1120) // it are entrys not cores 1120 seems enough for 256 cores
      {             // way to much if this would happen // safety
        break;
      }
    }
  }
  // part 1 (function) GetLogicalProcessorInformationEx Emu function end
  //

  // SYSTEM_PROCESSOR_INFORMATION
  // part 2 SYSTEM_PROCESSOR_INFORMATION for GetLogicalProcessorInformationEx
  // emu function SystemProcessorInformation_GetLogicalProcessorInformation
  NtQuerySystemInformation(
      (SYSTEM_INFORMATION_CLASS)0x00000001, // 0x00000001 =
                                             // SystemProcessorInformation
      (PVOID)&SYSTEM_PROCESSOR_INFORMATION_GetLogicalProcessorInformationEx,
      (ULONG)sizeof(
          SYSTEM_PROCESSOR_INFORMATION_GetLogicalProcessorInformationEx),
      &ReturnLength_GetLogicalProcessorInformationEx_SYSTEM_PROCESSOR_INFORMATION_01);
  // this function returns 0 but works
  // in a 8 core win10 the values where
  // Public Attributes
  // USHORT 	ProcessorArchitecture = 0x0000
  // USHORT 	ProcessorLevel = 0x0015
  // USHORT 	ProcessorRevision = 0x0200
  // USHORT 	MaximumProcessors(win8+)/or Reserved = win10 had 0x0008
  // ULONG 	ProcessorFeatureBits = 0xa8bb3dfe
  // part 2 SYSTEM_PROCESSOR_INFORMATION for GetLogicalProcessorInformationEx
  // emu function end SYSTEM_PROCESSOR_INFORMATION end
  //

  // SYSTEM_BASIC_INFORMATION
  // part 3 SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx emu
  // function - function begin
  NtQuerySystemInformation(
      SystemBasicInformation,
      (PVOID)&SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01,
      (ULONG)sizeof(
          SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01),
      &ReturnLengthGetLogicalProcessorInformationEx_SYSTEM_BASIC_INFORMATION_01);
  // this function returns 0 but works
  // tested on a 8 core cpu had this values:
  // KAFFINITY ActiveProcessorsAffinityMask was - 0x000000FF
  // CCHAR NumberOfProcessors was - 0x08
  // part 3 SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx emu
  // function - function end SYSTEM_BASIC_INFORMATION end
  //

  // part 4 setting the buffer for groups
  // setting SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer for group
  // PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer;
  //

  // LOGICAL_PROCESSOR_RELATIONSHIP RelationshipType,
  // PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX Buffer,
  // PDWORD ReturnedLength

  if (RelationshipType == RelationGroup) {

    if ((IsBadWritePtr(buffer, 0x0000004C))) // 0 if valid buffer
    {
      if (!(IsBadWritePtr(ReturnedLength, 0x00000004))) // 0 if invalid buffer
      {
        ReturnedLength = (PDWORD)(0x0000004C);
        return 0;
      }
      return 0;
    }

    buffer->Relationship = RelationGroup;
    buffer->Size =
        (DWORD)0x0000004C; // sizeof SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX
                           // (upper part) + GROUP_RELATIONSHIP

    buffer->DUMMYUNIONNAME.Group.MaximumGroupCount = (WORD)0x0001; // was 0x01
    buffer->DUMMYUNIONNAME.Group.ActiveGroupCount = (WORD)0x0001;  // was 0x01

    for (int i = 0; i < 20; i++) // [20]
    {
      buffer->DUMMYUNIONNAME.Group.Reserved[i] = (BYTE)0x00;
    }

    // in 8 core cpu had 0x08
    buffer->DUMMYUNIONNAME.Group.GroupInfo[0].MaximumProcessorCount =
        (BYTE)number_of_processorCoreCount_GetLogicalProcessorInformation;
    // possible vars - Group.GroupInfo.MaximumProcessorCount
    // SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01.NumberOfProcessors
    // number_of_processorCoreCount_GetLogicalProcessorInformation;
    // number_of_logicalProcessorCount_GetLogicalProcessorInformation;
    // not useable only win8+ !
    // SYSTEM_PROCESSOR_INFORMATION_GetLogicalProcessorInformationEx.MaximumProcessors

    // in 8 core cpu had 0x08
    buffer->DUMMYUNIONNAME.Group.GroupInfo[0].ActiveProcessorCount =
        (BYTE)number_of_processorCoreCount_GetLogicalProcessorInformation;
    // possible vars - Group.GroupInfo[0].ActiveProcessorCount - same or close
    // values what described at MaximumProcessorCount

    for (int i = 0; i < 38; i++) // <= ? buffer has 38 bytes but
    {
      buffer->DUMMYUNIONNAME.Group.GroupInfo[0].Reserved[i] = (BYTE)0x00;
    }

    // in 8 core cpu has 0x000000FF
    buffer->DUMMYUNIONNAME.Group.GroupInfo[0].ActiveProcessorMask =
        SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01
            .ActiveProcessorsAffinityMask;
    // possible vars - Group.GroupInfo[0].ActiveProcessorMask
    // SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01.ActiveProcessorsAffinityMask
    // ReturnedLength set maybe // size SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX
    // + GROUP_RELATIONSHIP = 0x0000004C

    if (!(IsBadWritePtr(ReturnedLength, 0x00000004))) {
      ReturnedLength = (PDWORD)(0x0000004C);
      return 1;
    }

    return 1;
  } // setting SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX buffer for group end
  //

  typedef struct
      _SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX_PROCESSOR_RELATIONSHIP {
    LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
    DWORD Size;
    union {
      PROCESSOR_RELATIONSHIP Processor;
    } DUMMYUNIONNAME;
  } SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX_PROCESSOR_RELATIONSHIP,
      *PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX_PROCESSOR_RELATIONSHIP;

  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX_PROCESSOR_RELATIONSHIP
      buffer_PROCESSOR_RELATIONSHIP;
  buffer_PROCESSOR_RELATIONSHIP =
      (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX_PROCESSOR_RELATIONSHIP)buffer;

  if (RelationshipType == RelationProcessorCore) {

    if ((IsBadWritePtr(buffer, 0x0000002C))) // 0 if valid buffer
    {
      if (!(IsBadWritePtr(ReturnedLength, 0x00000004))) // 0 if invalid buffer
      {
        ReturnedLength = (PDWORD)(
            number_of_processorCoreCount_GetLogicalProcessorInformation *
            0x0000002C);
        return 0;
      }
      return 0;
    }

    // has 1 entry per core - 8 cores have 8
    for (i_RelationProcessorCore = 0;
         i_RelationProcessorCore <
         number_of_processorCoreCount_GetLogicalProcessorInformation;
         i_RelationProcessorCore++) {
      buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore].Relationship =
          RelationProcessorCore;
      buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore].Size =
          (DWORD)0x0000002C; //(is size of 1
                             //_SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX (upper
                             //part)
      // + _PROCESSOR_RELATIONSHIP structure = total 0x2C )

      buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore]
          .DUMMYUNIONNAME.Processor.Flags =
          (BYTE)0x00; // was 0x00 has to be set

      if (number_of_logicalProcessorCount_GetLogicalProcessorInformation >
          number_of_processorCoreCount_GetLogicalProcessorInformation) { // flags
                                                                         // for
                                                                         // logicalprocessors
                                                                         // have
                                                                         // -
                                                                         // LTP_PC_SMT
                                                                         // -
                                                                         // #define
                                                                         // LTP_PC_SMT
                                                                         // 0x1
        buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore]
            .DUMMYUNIONNAME.Processor.Flags =
            (BYTE)0x01; // was 0x00 has to be set
      }

      buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore]
          .DUMMYUNIONNAME.Processor.EfficiencyClass = (BYTE)0x00; // was 0x00

      for (int i = 0; i < 20; i++) // [20]
      {
        buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore]
            .DUMMYUNIONNAME.Processor.Reserved[i] =
            (BYTE)0x00; // all where 0x00
      }

      buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore]
          .DUMMYUNIONNAME.Processor.GroupCount =
          (WORD)0x0001; // where always 0x0001

      //  buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore].Processor.GroupMask[0].Mask
      //  =
      //  (DWORD)SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01.ActiveProcessorsAffinityMask
      //  >> (number_of_processorCoreCount_GetLogicalProcessorInformation -
      //  i_RelationProcessorCore);
      buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore]
          .DUMMYUNIONNAME.Processor.GroupMask[0]
          .Mask = (unsigned int)0x00000001 << i_RelationProcessorCore;
      // possible vars combined with - GroupMask[0].Mask
      // SYSTEM_BASIC_INFORMATION_GetLogicalProcessorInformationEx_01.NumberOfProcessors
      // number_of_processorCoreCount_GetLogicalProcessorInformation;
      // number_of_logicalProcessorCount_GetLogicalProcessorInformation;
      // not useable only win8+ !
      // SYSTEM_PROCESSOR_INFORMATION_GetLogicalProcessorInformationEx.MaximumProcessors
      // in 8 core cpu has 0x000000FF for ActiveProcessorMask
      buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore]
          .DUMMYUNIONNAME.Processor.GroupMask[0]
          .Group = (WORD)0x0000; // where 0x0000

      for (int i = 0; i < 3; i++) // Reserved[3] // where all 0x0000
      {
        buffer_PROCESSOR_RELATIONSHIP[i_RelationProcessorCore]
            .DUMMYUNIONNAME.Processor.GroupMask[0]
            .Reserved[i] = (WORD)0x0000;
      }
    }

    if (!(IsBadWritePtr(ReturnedLength, 0x00000004))) {
      ReturnedLength =
          (PDWORD)(number_of_processorCoreCount_GetLogicalProcessorInformation *
                   0x0000002C);
    }

    return 1;
  }

  return 0;
};
// GetLogicalProcessorInformationEx_Emu function end


//
// GetProcessGroupAffinity emu begin
unsigned short GroupArray_GetProcessGroupAffinity_Emu[4] = 
{0x0000, 0x0000, 0x0000, 0x0000}; //
//{0x0000, 0x0000, 0x0000, 0x0000}; 
USHORT GroupCount_GetProcessGroupAffinity_Emu = 0x0001;   // number of groups
//__declspec(noreturn)
//__declGetThreadIdspec(noinline)

__declspec(noinline) BOOL WINAPI
    GetProcessGroupAffinityX(HANDLE hProcess, PUSHORT GroupCount,
                             PUSHORT GroupArray) {
  if ((IsBadWritePtr(GroupArray, 0x00000004))) {
    return 0;
  }

  if ((IsBadWritePtr(GroupCount, 0x00000004))) {
    return 0;
  }

  *GroupCount = (USHORT)GroupCount_GetProcessGroupAffinity_Emu;

  for (int i = 0; i < GroupCount_GetProcessGroupAffinity_Emu; i++) {
    GroupArray[i] = (USHORT)0x0000;
  }

  return 1;
};
// GetProcessGroupAffinity emu end
//