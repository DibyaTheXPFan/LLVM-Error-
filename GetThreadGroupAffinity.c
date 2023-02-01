

BOOL __GetThreadGroupAffinity(HANDLE hThread, PGROUP_AFFINITY affinity)
{
    // Don't do anything when targetting OneCore (We could set it to active processor mask in the future)
#if !defined(_ONECORE)
#if defined(DYNAMIC_AFFINITY_FUNCTIONS)
    if (::Concurrency::GetOSVersion() >= ::Concurrency::IResourceManager::Win7OrLater)
    {
        PFnGetThreadGroupAffinity fnDecodedFunction = (PFnGetThreadGroupAffinity) Security::DecodePointer(s_pfnGetThreadGroupAffinity);
        CONCRT_VERIFY(fnDecodedFunction(hThread, affinity));
    }
    else
    {
        // On operating systems older than Win7, we don't have access to the correct information about thread's affinity,
        // so we will assume that the affinity is that of the process.
        DWORD_PTR pProcessAffinityMask;
        DWORD_PTR pSystemAffinityMask;

        GetProcessAffinityMask(GetCurrentProcess(), &pProcessAffinityMask, &pSystemAffinityMask);
        affinity->Group = 0;
        affinity->Mask = pProcessAffinityMask;
    }
#else   // !defined(DYNAMIC_AFFINITY_FUNCTIONS)
 //   CONCRT_VERIFY(GetThreadGroupAffinity(hThread, affinity));
#endif  // !defined(DYNAMIC_AFFINITY_FUNCTIONS)
#endif // !defined(_ONECORE)

    return 1;
}

BOOL __GetThreadGroupAffinity(HANDLE hThread, PGROUP_AFFINITY affinity)
{
    // Don't do anything when targetting OneCore (We could set it to active processor mask in the future)
#if !defined(_ONECORE)
#if defined(DYNAMIC_AFFINITY_FUNCTIONS)
    if (::Concurrency::GetOSVersion() >= ::Concurrency::IResourceManager::Win7OrLater)
    {
        PFnGetThreadGroupAffinity fnDecodedFunction = (PFnGetThreadGroupAffinity) Security::DecodePointer(s_pfnGetThreadGroupAffinity);
        CONCRT_VERIFY(fnDecodedFunction(hThread, affinity));
    }
    else
    {
        // On operating systems older than Win7, we don't have access to the correct information about thread's affinity,
        // so we will assume that the affinity is that of the process.
        DWORD_PTR pProcessAffinityMask;
        DWORD_PTR pSystemAffinityMask;

        GetProcessAffinityMask(GetCurrentProcess(), &pProcessAffinityMask, &pSystemAffinityMask);
        affinity->Group = 0;
        affinity->Mask = pProcessAffinityMask;
    }
#else   // !defined(DYNAMIC_AFFINITY_FUNCTIONS)
 //   CONCRT_VERIFY(GetThreadGroupAffinity(hThread, affinity));
#endif  // !defined(DYNAMIC_AFFINITY_FUNCTIONS)
#endif // !defined(_ONECORE)

    return 1;
}








// checks 
// DYNAMIC_AFFINITY_FUNCTIONS
// _ONECORE

























// above is windows solution it useally takes it if not try to set the right 
// right flags or defs what are needed if not code is below
// depending where it is placed define the imports and vars , if imports and vars are defined dont def vars and imports

typedef int BOOL;
typedef unsigned short WORD;

typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
typedef ULONG_PTR KAFFINITY;
typedef KAFFINITY *PKAFFINITY;

typedef struct _GROUP_AFFINITY {
  KAFFINITY Mask;
  WORD Group;
  WORD Reserved[3];
} GROUP_AFFINITY, *PGROUP_AFFINITY;

__declspec(dllimport) 
BOOL
__stdcall 
GetProcessAffinityMask(HANDLE hProcess,
                       PDWORD_PTR lpProcessAffinityMask,
                       PDWORD_PTR lpSystemAffinityMask);

__declspec(dllimport)
DWORD_PTR
__stdcall
SetThreadAffinityMask(HANDLE hThread, DWORD_PTR dwThreadAffinityMask);

__declspec(dllimport)
HANDLE 
__stdcall 
GetCurrentProcess(VOID);


BOOL GetThreadGroupAffinityX(HANDLE hThread, PGROUP_AFFINITY affinity) 
{
  DWORD_PTR pProcessAffinityMask;
  DWORD_PTR pSystemAffinityMask;

  GetProcessAffinityMask(GetCurrentProcess(), &pProcessAffinityMask,
                         &pSystemAffinityMask);
  affinity->Group = 0;
  affinity->Mask = pProcessAffinityMask;
  return 1;
}

BOOL SetThreadGroupAffinityX(HANDLE hThread, const GROUP_AFFINITY *affinity) 
{
  SetThreadAffinityMask(hThread, affinity->Mask);
  return 1;
}

