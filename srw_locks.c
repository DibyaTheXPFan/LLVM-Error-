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
#define ThreadBasicInformation 0x00
typedef BYTE BOOLEAN;
typedef BOOLEAN *PBOOLEAN;  
typedef LONG *PLONG;    
#define assert(expression) ((void)0)
typedef LONG NTSTATUS;
typedef __int64 LONGLONG;
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#define NULL 0
#define FAR far

#define DECLARE_HANDLE(name)                                                   \
  struct name##__ {                                                            \
    int unused;                                                                \
  };                                                                           \
  typedef struct name##__ *name
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG HighPart;
  } DUMMYSTRUCTNAME;
  struct {
    DWORD LowPart;
    LONG HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER;
typedef ULONG_PTR SIZE_T, *PSIZE_T;
typedef LARGE_INTEGER *PLARGE_INTEGER;

typedef int(FAR __stdcall *FARPROC)();
#define WINAPI __stdcall
#define NTAPI __stdcall
#define WINAPI __stdcall
#define DECLSPEC_IMPORT __declspec(dllimport)
#define WINBASEAPI DECLSPEC_IMPORT
#define FORCEINLINE __forceinline
#define CDECL_NON_WVMPURE __cdecl

typedef enum _THREADINFOCLASS { ThreadIsIoPending = 16 } THREADINFOCLASS;

#define ERROR_INVALID_PARAMETER 87L // dderror

typedef union _RTL_RUN_ONCE {
  PVOID Ptr;
} RTL_RUN_ONCE, *PRTL_RUN_ONCE;
typedef RTL_RUN_ONCE INIT_ONCE;

typedef struct _RTLP_SRWLOCK_SHARED_WAKE {
  LONG Wake;
  volatile struct _RTLP_SRWLOCK_SHARED_WAKE *Next;
} volatile RTLP_SRWLOCK_SHARED_WAKE, *PRTLP_SRWLOCK_SHARED_WAKE;

typedef struct _RTLP_SRWLOCK_WAITBLOCK {
  // SharedCount is the number of shared acquirers.
  LONG SharedCount;

  // Last points to the last wait block in the chain. The value
  //   is only valid when read from the first wait block.
  volatile struct _RTLP_SRWLOCK_WAITBLOCK *Last;

  // Next points to the next wait block in the chain.
  volatile struct _RTLP_SRWLOCK_WAITBLOCK *Next;

  union {
    // Wake is only valid for exclusive wait blocks
    LONG Wake;
    // The wake chain is only valid for shared wait blocks
    struct {
      PRTLP_SRWLOCK_SHARED_WAKE SharedWakeChain;
      PRTLP_SRWLOCK_SHARED_WAKE LastSharedWake;
    };
  };

  BOOLEAN Exclusive;
} volatile RTLP_SRWLOCK_WAITBLOCK, *PRTLP_SRWLOCK_WAITBLOCK;

typedef struct _RTL_SRWLOCK {
  PVOID Ptr;
} RTL_SRWLOCK, *PRTL_SRWLOCK;

#define InterlockedCompareExchange _InterlockedCompareExchange

#define InterlockedCompareExchangePointer                                      \
  _InlineInterlockedCompareExchangePointer

VOID _mm_pause(VOID);

#define YieldProcessor _mm_pause

#define EXCEPTION_MAXIMUM_PARAMETERS                                           \
  15 // maximum number of exception parameters

typedef struct _EXCEPTION_RECORD {
  DWORD ExceptionCode;
  DWORD ExceptionFlags;
  struct _EXCEPTION_RECORD *ExceptionRecord;
  PVOID ExceptionAddress;
  DWORD NumberParameters;
  ULONG_PTR ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
} EXCEPTION_RECORD;

#define EXCEPTION_NONCONTINUABLE 0x1
typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define STATUS_PENDING ((DWORD)0x00000103L)
#define STATUS_UNSUCCESSFUL ((NTSTATUS)0xC0000001L)
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define STATUS_RESOURCE_NOT_OWNED ((NTSTATUS)0xC0000264L)
#define STATUS_INVALID_PARAMETER ((DWORD)0xC000000DL)  

#define RTL_RUN_ONCE_CHECK_ONLY 0x00000001UL
#define RTL_RUN_ONCE_ASYNC 0x00000002UL
#define RTL_RUN_ONCE_INIT_FAILED 0x00000004UL

__declspec(dllimport) HMODULE __stdcall LoadLibraryW(LPCWSTR lpLibFileName);

__declspec(dllimport) HMODULE __stdcall GetModuleHandleW(LPCWSTR lpModuleName);

__declspec(dllimport) FARPROC
    __stdcall GetProcAddress(HMODULE hModule, LPCSTR lpProcName);

__declspec(dllimport) VOID
    __stdcall RtlRaiseException( PEXCEPTION_RECORD ExceptionRecord);

WINBASEAPI
VOID WINAPI SetLastError(DWORD dwErrCode);

ULONG
NTAPI
RtlNtStatusToDosError(NTSTATUS Status);


LONG CDECL_NON_WVMPURE InterlockedCompareExchange(LONG volatile *Destination,
                                                  LONG ExChange,
                                                  LONG Comperand);

LONG InterlockedOr(LONG volatile *Destination, LONG Value);

LONG InterlockedAnd(LONG volatile *Destination,
                    LONG Value);
LONG __cdecl InterlockedExchange(
    LONG volatile *Target, LONG Value);

#define InterlockedOr _InterlockedOr
#define InterlockedAnd _InterlockedAnd
#define InterlockedExchangePointer _InlineInterlockedExchangePointer

#define InterlockedExchange _InterlockedExchange

#define InterlockedCompareExchangePointer                                      \
  _InlineInterlockedCompareExchangePointer

FORCEINLINE
PVOID _InlineInterlockedExchangePointer(
PVOID volatile *Destination,
PVOID Value) 
{
  return (PVOID)InterlockedExchange((LONG volatile *)Destination, (LONG)Value);
}

FORCEINLINE
PVOID
_InlineInterlockedCompareExchangePointer(PVOID volatile *Destination,
                                         PVOID ExChange, PVOID Comperand) {
  return (PVOID)InterlockedCompareExchange((LONG volatile *)Destination,
                                           (LONG)ExChange, (LONG)Comperand);
}

#define BitTest _bittest
#define BitTestAndComplement _bittestandcomplement
#define BitTestAndSet _bittestandset
#define BitTestAndReset _bittestandreset
#define InterlockedBitTestAndSet _interlockedbittestandset
#define InterlockedBitTestAndSetAcquire _interlockedbittestandset
#define InterlockedBitTestAndSetRelease _interlockedbittestandset
#define InterlockedBitTestAndSetNoFence _interlockedbittestandset
#define InterlockedBitTestAndReset _interlockedbittestandreset
#define InterlockedBitTestAndResetAcquire _interlockedbittestandreset
#define InterlockedBitTestAndResetRelease _interlockedbittestandreset
#define InterlockedBitTestAndResetNoFence _interlockedbittestandreset

#define InterlockedBitTestAndSetPointer(ptr, val)                              \
  InterlockedBitTestAndSet((PLONG)ptr, (LONG)val)


BOOLEAN _bittest(LONG const *Base, LONG Offset);

BOOLEAN
_bittestandcomplement(LONG *Base, LONG Offset);

BOOLEAN
_bittestandset(LONG *Base, LONG Offset);

BOOLEAN
_bittestandreset(LONG *Base, LONG Offset);

BOOLEAN
_interlockedbittestandset(LONG volatile *Base, LONG Offset);

BOOLEAN
_interlockedbittestandreset(LONG volatile *Base, LONG Offset);

#pragma intrinsic(_bittest)
#pragma intrinsic(_bittestandcomplement)
#pragma intrinsic(_bittestandset)
#pragma intrinsic(_bittestandreset)
#pragma intrinsic(_interlockedbittestandset)
#pragma intrinsic(_interlockedbittestandreset)


#ifdef _WIN64
#define InterlockedBitTestAndSetPointer(ptr, val)                              \
  InterlockedBitTestAndSet64((PLONGLONG)ptr, (LONGLONG)val)
#define InterlockedAddPointer(ptr, val)                                        \
  InterlockedAdd64((PLONGLONG)ptr, (LONGLONG)val)
#define InterlockedAndPointer(ptr, val)                                        \
  InterlockedAnd64((PLONGLONG)ptr, (LONGLONG)val)
#define InterlockedOrPointer(ptr, val)                                         \
  InterlockedOr64((PLONGLONG)ptr, (LONGLONG)val)
#define _ONE 1LL
#else
#define InterlockedBitTestAndSetPointer(ptr, val)                              \
  InterlockedBitTestAndSet((PLONG)ptr, (LONG)val)
#define InterlockedAddPointer(ptr, val) InterlockedAdd((PLONG)ptr, (LONG)val)
#define InterlockedAndPointer(ptr, val) InterlockedAnd((PLONG)ptr, (LONG)val)
#define InterlockedOrPointer(ptr, val) InterlockedOr((PLONG)ptr, (LONG)val)
#define _ONE 1L
#endif


#define RTL_SRWLOCK_OWNED_BIT 0
#define RTL_SRWLOCK_CONTENDED_BIT 1
#define RTL_SRWLOCK_SHARED_BIT 2
#define RTL_SRWLOCK_CONTENTION_LOCK_BIT 3
#define RTL_SRWLOCK_OWNED (_ONE << RTL_SRWLOCK_OWNED_BIT)
#define RTL_SRWLOCK_CONTENDED (_ONE << RTL_SRWLOCK_CONTENDED_BIT)
#define RTL_SRWLOCK_SHARED (_ONE << RTL_SRWLOCK_SHARED_BIT)
#define RTL_SRWLOCK_CONTENTION_LOCK (_ONE << RTL_SRWLOCK_CONTENTION_LOCK_BIT)
#define RTL_SRWLOCK_MASK                                                       \
  (RTL_SRWLOCK_OWNED | RTL_SRWLOCK_CONTENDED | RTL_SRWLOCK_SHARED |            \
   RTL_SRWLOCK_CONTENTION_LOCK)
#define RTL_SRWLOCK_BITS 4

#define __MACHINE(X) X;
__MACHINE(void *_ReturnAddress(void))

//#ifndef RtlRaiseStatus
VOID NTAPI RtlRaiseStatus(NTSTATUS Status) {
  EXCEPTION_RECORD ExceptionRecord;
  //	CONTEXT Context;

  // Capture the context
  //	RtlCaptureContext(&Context);

  // Create an exception record
  ExceptionRecord.ExceptionAddress = _ReturnAddress();
  ExceptionRecord.ExceptionCode = Status;
  ExceptionRecord.ExceptionRecord = NULL;
  ExceptionRecord.NumberParameters = 0;
  ExceptionRecord.ExceptionFlags = EXCEPTION_NONCONTINUABLE;

  RtlRaiseException(&ExceptionRecord);
}
//#endif






// NTSYSCALLAPI
NTSTATUS(NTAPI *NtReleaseKeyedEvent)(
HANDLE EventHandle, 
PVOID Key, 
BOOLEAN Alertable,
PLARGE_INTEGER Timeout) = 0x00000000;

HMODULE hModule_ntdll_NtReleaseKeyedEvent_Switch = 0x00000000;

NTSTATUS
NTAPI
NtReleaseKeyedEvent_Switch(
HANDLE EventHandle, 
PVOID Key,
BOOLEAN Alertable,
PLARGE_INTEGER Timeout) {

  if (NtReleaseKeyedEvent) {
    return NtReleaseKeyedEvent(EventHandle, Key, Alertable, Timeout);
  }

  hModule_ntdll_NtReleaseKeyedEvent_Switch = LoadLibraryW(L"ntdll.dll");

  NtReleaseKeyedEvent =
      (NTSTATUS(__stdcall *)(HANDLE, PVOID, BOOLEAN, PLARGE_INTEGER))
          GetProcAddress(hModule_ntdll_NtReleaseKeyedEvent_Switch,
                         "NtReleaseKeyedEvent");

  if (!hModule_ntdll_NtReleaseKeyedEvent_Switch) {
    hModule_ntdll_NtReleaseKeyedEvent_Switch = GetModuleHandleW(L"ntdll.dll");
    NtReleaseKeyedEvent =
        (NTSTATUS(__stdcall *)(HANDLE, PVOID, BOOLEAN, PLARGE_INTEGER))
            GetProcAddress(hModule_ntdll_NtReleaseKeyedEvent_Switch,
                           "NtReleaseKeyedEvent");
  }

  if (NtReleaseKeyedEvent) {
    return NtReleaseKeyedEvent(EventHandle, Key, Alertable, Timeout);
  }

  return FALSE;
}


// NtWaitForKeyedEvent
// NTSYSCALLAPI // winnt __declspec(dllimport)
NTSTATUS
    // NTAPI
    (NTAPI *NtWaitForKeyedEvent)(HANDLE EventHandle, PVOID Key,
                                 BOOLEAN Alertable,
                                 PLARGE_INTEGER Timeout) = 0x00000000;


HMODULE hModule_ntdll_NtWaitForKeyedEvent_Switch = 0x00000000; // own var for independency
NTSTATUS 
NTAPI
NtWaitForKeyedEvent_Switch(HANDLE EventHandle, PVOID Key,
                               BOOLEAN Alertable,
                               PLARGE_INTEGER Timeout) 
{

  if (NtWaitForKeyedEvent) 
  {
    return NtWaitForKeyedEvent(EventHandle, Key, Alertable, Timeout);
  }

  hModule_ntdll_NtWaitForKeyedEvent_Switch = LoadLibraryW(L"ntdll.dll");

  NtWaitForKeyedEvent =
      (NTSTATUS(__stdcall *)(HANDLE, PVOID, BOOLEAN, PLARGE_INTEGER))
          GetProcAddress(hModule_ntdll_NtWaitForKeyedEvent_Switch,
                         "NtWaitForKeyedEvent");

  if (!hModule_ntdll_NtWaitForKeyedEvent_Switch) 
  {
    hModule_ntdll_NtWaitForKeyedEvent_Switch = GetModuleHandleW(L"ntdll.dll");
    NtWaitForKeyedEvent =
        (NTSTATUS(__stdcall *)(HANDLE, PVOID, BOOLEAN, PLARGE_INTEGER))
            GetProcAddress(hModule_ntdll_NtWaitForKeyedEvent_Switch,
                           "NtWaitForKeyedEvent");
  }

  if (NtWaitForKeyedEvent) {
    return NtWaitForKeyedEvent(EventHandle, Key, Alertable, Timeout);
  }

  return FALSE;
}


// RtlRunOnceBeginInitialize
// Taken from Wine ntdll/sync.c
// HANDLE keyed_event = NULL;
DWORD
WINAPI
RtlRunOnceBeginInitialize(RTL_RUN_ONCE *once, ULONG flags, void **context) {
  if (flags & RTL_RUN_ONCE_CHECK_ONLY) {
    ULONG_PTR val = (ULONG_PTR)once->Ptr;

    if (flags & RTL_RUN_ONCE_ASYNC)
      return STATUS_INVALID_PARAMETER;
    if ((val & 3) != 2)
      return STATUS_UNSUCCESSFUL;
    if (context)
      *context = (void *)(val & ~3);
    return STATUS_SUCCESS;
  }

  for (;;) {
    ULONG_PTR next, val = (ULONG_PTR)once->Ptr;

    switch (val & 3) {
    case 0: // first time
      // if (!interlocked_cmpxchg_ptr(&once->Ptr,
      if (!InterlockedCompareExchangePointer(
              &once->Ptr, (flags & RTL_RUN_ONCE_ASYNC) ? (void *)3 : (void *)1,
              0))
        return STATUS_PENDING;
      break;

    case 1: // in progress, wait
      if (flags & RTL_RUN_ONCE_ASYNC)
        return STATUS_INVALID_PARAMETER;
      next = val & ~3;
      // if (interlocked_cmpxchg_ptr(&once->Ptr, (void*)((ULONG_PTR)&next | 1),
      if (InterlockedCompareExchangePointer(&once->Ptr,
                                            (void *)((ULONG_PTR)&next | 1),
                                            (void *)val) == (void *)val)
        // questionable
        //  NtWaitForKeyedEvent(keyed_event, &next, FALSE, NULL);// handle is 0
        NtWaitForKeyedEvent(0, &next, FALSE, NULL);
      break;

    case 2: // done
      if (context)
        *context = (void *)(val & ~3);
      return STATUS_SUCCESS;

    case 3: // in progress, async
      if (!(flags & RTL_RUN_ONCE_ASYNC))
        return STATUS_INVALID_PARAMETER;
      return STATUS_PENDING;
    }
  }
}

// RtlRunOnceComplete
DWORD WINAPI RtlRunOnceComplete(RTL_RUN_ONCE *once, ULONG flags,
                                void *context) {
  if ((ULONG_PTR)context & 3)
    return STATUS_INVALID_PARAMETER;

  if (flags & RTL_RUN_ONCE_INIT_FAILED) {
    if (context)
      return STATUS_INVALID_PARAMETER;
    if (flags & RTL_RUN_ONCE_ASYNC)
      return STATUS_INVALID_PARAMETER;
  } else
    context = (void *)((ULONG_PTR)context | 2);

  for (;;) {
    ULONG_PTR val = (ULONG_PTR)once->Ptr;

    switch (val & 3) {
    case 1: // in progress
      if (InterlockedCompareExchangePointer(&once->Ptr, context, (void *)val) !=
          (void *)val)
        break;
      val &= ~3;
      while (val) {
        ULONG_PTR next = *(ULONG_PTR *)val;
        NtReleaseKeyedEvent(0, (void *)val, FALSE, NULL);
        val = next;
      }
      return STATUS_SUCCESS;

    case 3: // in progress, async
      if (!(flags & RTL_RUN_ONCE_ASYNC))
        return STATUS_INVALID_PARAMETER;
      if (InterlockedCompareExchangePointer(&once->Ptr, context, (void *)val) !=
          (void *)val)
        break;
      return STATUS_SUCCESS;

    default:
      return STATUS_UNSUCCESSFUL;
    }
  }
}

__declspec(noinline) BOOL WINAPI
    InitOnceCompleteX(INIT_ONCE *once, DWORD flags, void *context) {
  NTSTATUS status = RtlRunOnceComplete(once, flags, context);
  if (status != STATUS_SUCCESS)
    SetLastError(RtlNtStatusToDosError(status));
  return !status;
}


__declspec(noinline) BOOL WINAPI
    InitOnceBeginInitializeX(INIT_ONCE *once, DWORD flags, BOOL *pending,
                             void **context) {
  NTSTATUS status = RtlRunOnceBeginInitialize(once, flags, context);
  if (NT_SUCCESS(status)) {
    *pending = (status == STATUS_PENDING);
  } else {
    SetLastError(RtlNtStatusToDosError(status));
  }
  return status >= 0;
}

static VOID NTAPI RtlpReleaseWaitBlockLockExclusive(
  PRTL_SRWLOCK SRWLock, PRTLP_SRWLOCK_WAITBLOCK FirstWaitBlock) {
  PRTLP_SRWLOCK_WAITBLOCK Next;
  LONG_PTR NewValue;

  // NOTE: We're currently in an exclusive lock in contended mode.

  Next = FirstWaitBlock->Next;
  if (Next != NULL) {
    // There's more blocks chained, we need to update the pointers
    //   in the next wait block and update the wait block pointer.
    NewValue = (LONG_PTR)Next | RTL_SRWLOCK_OWNED | RTL_SRWLOCK_CONTENDED;
    if (!FirstWaitBlock->Exclusive) {
      // The next wait block has to be an exclusive lock!
      assert(Next->Exclusive);

      // Save the shared count
      Next->SharedCount = FirstWaitBlock->SharedCount;

      NewValue |= RTL_SRWLOCK_SHARED;
    }

    Next->Last = FirstWaitBlock->Last;
  } else {
    // Convert the lock to a simple lock.
    if (FirstWaitBlock->Exclusive)
      NewValue = RTL_SRWLOCK_OWNED;
    else {
      assert(FirstWaitBlock->SharedCount > 0);

      NewValue = ((LONG_PTR)FirstWaitBlock->SharedCount << RTL_SRWLOCK_BITS) |
                 RTL_SRWLOCK_SHARED | RTL_SRWLOCK_OWNED;
    }
  }

  (void)InterlockedExchangePointer(&SRWLock->Ptr, (PVOID)NewValue);

  if (FirstWaitBlock->Exclusive) {
    (void)InterlockedOr(&FirstWaitBlock->Wake, TRUE);
  } else {
    PRTLP_SRWLOCK_SHARED_WAKE WakeChain, NextWake;

    // If we were the first one to acquire the shared
    // lock, we now need to wake all others...
    WakeChain = FirstWaitBlock->SharedWakeChain;
    do {
      NextWake = WakeChain->Next;

      (void)InterlockedOr((PLONG)&WakeChain->Wake, TRUE);

      WakeChain = NextWake;
    } while (WakeChain != NULL);
  }
}

static VOID NTAPI RtlpReleaseWaitBlockLockLastShared(
  PRTL_SRWLOCK SRWLock, PRTLP_SRWLOCK_WAITBLOCK FirstWaitBlock) {
  PRTLP_SRWLOCK_WAITBLOCK Next;
  LONG_PTR NewValue;

  // NOTE: We're currently in a shared lock in contended mode.

  // The next acquirer to be unwaited *must* be an exclusive lock!
  assert(FirstWaitBlock->Exclusive);

  Next = FirstWaitBlock->Next;
  if (Next != NULL) {
    // There's more blocks chained, we need to update the pointers
    // in the next wait block and update the wait block pointer.
    NewValue = (LONG_PTR)Next | RTL_SRWLOCK_OWNED | RTL_SRWLOCK_CONTENDED;

    Next->Last = FirstWaitBlock->Last;
  } else {
    // Convert the lock to a simple exclusive lock.
    NewValue = RTL_SRWLOCK_OWNED;
  }

  (void)InterlockedExchangePointer(&SRWLock->Ptr, (PVOID)NewValue);

  (void)InterlockedOr(&FirstWaitBlock->Wake, TRUE);
}

static VOID NTAPI RtlpReleaseWaitBlockLock(PRTL_SRWLOCK SRWLock) {
  InterlockedAndPointer(&SRWLock->Ptr, ~RTL_SRWLOCK_CONTENTION_LOCK);
}

static PRTLP_SRWLOCK_WAITBLOCK NTAPI
RtlpAcquireWaitBlockLock(PRTL_SRWLOCK SRWLock) {
  LONG_PTR PrevValue;
  PRTLP_SRWLOCK_WAITBLOCK WaitBlock;

  while (1) {
    PrevValue =
        InterlockedOrPointer(&SRWLock->Ptr, RTL_SRWLOCK_CONTENTION_LOCK);

    if (!(PrevValue & RTL_SRWLOCK_CONTENTION_LOCK))
      break;

    YieldProcessor();
  }

  if (!(PrevValue & RTL_SRWLOCK_CONTENDED) ||
      (PrevValue & ~RTL_SRWLOCK_MASK) == 0) {
    // Too bad, looks like the wait block was removed in the
    // meanwhile, unlock again
    RtlpReleaseWaitBlockLock(SRWLock);
    return NULL;
  }

  WaitBlock = (PRTLP_SRWLOCK_WAITBLOCK)(PrevValue & ~RTL_SRWLOCK_MASK);

  return WaitBlock;
}

static VOID NTAPI RtlpAcquireSRWLockExclusiveWait(
    PRTL_SRWLOCK SRWLock, PRTLP_SRWLOCK_WAITBLOCK WaitBlock) {
  LONG_PTR CurrentValue;

  while (1) {
    CurrentValue = *(volatile LONG_PTR *)&SRWLock->Ptr;
    if (!(CurrentValue & RTL_SRWLOCK_SHARED)) {
      if (CurrentValue & RTL_SRWLOCK_CONTENDED) {
        if (WaitBlock->Wake != 0) {
          // Our wait block became the first one
          // in the chain, we own the lock now!
          break;
        }
      } else {
        // The last wait block was removed and/or we're
        // finally a simple exclusive lock. This means we
        // don't need to wait anymore, we acquired the lock!
        break;
      }
    }

    YieldProcessor();
  }
}

static VOID NTAPI
RtlpAcquireSRWLockSharedWait(PRTL_SRWLOCK SRWLock,
                             PRTLP_SRWLOCK_WAITBLOCK FirstWait,
                             PRTLP_SRWLOCK_SHARED_WAKE WakeChain) {
  if (FirstWait != NULL) {
    while (WakeChain->Wake == 0) {
      YieldProcessor();
    }
  } else {
    LONG_PTR CurrentValue;

    while (1) {
      CurrentValue = *(volatile LONG_PTR *)&SRWLock->Ptr;
      if (CurrentValue & RTL_SRWLOCK_SHARED) {
        // The RTL_SRWLOCK_OWNED bit always needs to be set when
        // RTL_SRWLOCK_SHARED is set!
        assert(CurrentValue & RTL_SRWLOCK_OWNED);

        if (CurrentValue & RTL_SRWLOCK_CONTENDED) {
          if (WakeChain->Wake != 0) {
            // Our wait block became the first one
            // in the chain, we own the lock now!
            break;
          }
        } else {
          // The last wait block was removed and/or we're
          // finally a simple shared lock. This means we
          // don't need to wait anymore, we acquired the lock!
          break;
        }
      }

      YieldProcessor();
    }
  }
}

VOID NTAPI RtlInitializeSRWLock(PRTL_SRWLOCK SRWLock) {
  SRWLock->Ptr = NULL;
}

__declspec(noinline) VOID NTAPI
    RtlAcquireSRWLockShared(PRTL_SRWLOCK SRWLock) {
  __declspec(align(16)) RTLP_SRWLOCK_WAITBLOCK StackWaitBlock;
  RTLP_SRWLOCK_SHARED_WAKE SharedWake;
  LONG_PTR CurrentValue, NewValue;
  PRTLP_SRWLOCK_WAITBLOCK First, Shared, FirstWait;

  while (1) {
    CurrentValue = *(volatile LONG_PTR *)&SRWLock->Ptr;

    if (CurrentValue & RTL_SRWLOCK_SHARED) {
      // NOTE: It is possible that the RTL_SRWLOCK_OWNED bit is set!

      if (CurrentValue & RTL_SRWLOCK_CONTENDED) {
        // There's other waiters already, lock the wait blocks and
        // increment the shared count
        First = RtlpAcquireWaitBlockLock(SRWLock);
        if (First != NULL) {
          FirstWait = NULL;

          if (First->Exclusive) {
            // We need to setup a new wait block! Although
            // we're currently in a shared lock and we're acquiring
            // a shared lock, there are exclusive locks queued. We need
            // to wait until those are released.
            Shared = First->Last;

            if (Shared->Exclusive) {
              StackWaitBlock.Exclusive = FALSE;
              StackWaitBlock.SharedCount = 1;
              StackWaitBlock.Next = NULL;
              StackWaitBlock.Last = &StackWaitBlock;
              StackWaitBlock.SharedWakeChain = &SharedWake;

              Shared->Next = &StackWaitBlock;
              First->Last = &StackWaitBlock;

              Shared = &StackWaitBlock;
              FirstWait = &StackWaitBlock;
            } else {
              Shared->LastSharedWake->Next = &SharedWake;
              Shared->SharedCount++;
            }
          } else {
            Shared = First;
            Shared->LastSharedWake->Next = &SharedWake;
            Shared->SharedCount++;
          }

          SharedWake.Next = NULL;
          SharedWake.Wake = 0;

          Shared->LastSharedWake = &SharedWake;

          RtlpReleaseWaitBlockLock(SRWLock);

          RtlpAcquireSRWLockSharedWait(SRWLock, FirstWait, &SharedWake);

          // Successfully incremented the shared count, we acquired the lock
          break;
        }
      } else {
        // This is a fastest path, just increment the number of
        //  current shared locks

        // Since the RTL_SRWLOCK_SHARED bit is set, the RTL_SRWLOCK_OWNED bit
        // also has to be set!

        assert(CurrentValue & RTL_SRWLOCK_OWNED);

        NewValue = (CurrentValue >> RTL_SRWLOCK_BITS) + 1;
        NewValue =
            (NewValue << RTL_SRWLOCK_BITS) | (CurrentValue & RTL_SRWLOCK_MASK);

        if ((LONG_PTR)InterlockedCompareExchangePointer(
                &SRWLock->Ptr, (PVOID)NewValue, (PVOID)CurrentValue) ==
            CurrentValue) {
          // Successfully incremented the shared count, we acquired the lock
          break;
        }
      }
    } else {
      if (CurrentValue & RTL_SRWLOCK_OWNED) {
        // The resource is currently acquired exclusively
        if (CurrentValue & RTL_SRWLOCK_CONTENDED) {
          SharedWake.Next = NULL;
          SharedWake.Wake = 0;

          // There's other waiters already, lock the wait blocks and
          // increment the shared count. If the last block in the chain
          // is an exclusive lock, add another block.

          StackWaitBlock.Exclusive = FALSE;
          StackWaitBlock.SharedCount = 0;
          StackWaitBlock.Next = NULL;
          StackWaitBlock.Last = &StackWaitBlock;
          StackWaitBlock.SharedWakeChain = &SharedWake;

          First = RtlpAcquireWaitBlockLock(SRWLock);
          if (First != NULL) {
            Shared = First->Last;
            if (Shared->Exclusive) {
              Shared->Next = &StackWaitBlock;
              First->Last = &StackWaitBlock;

              Shared = &StackWaitBlock;
              FirstWait = &StackWaitBlock;
            } else {
              FirstWait = NULL;
              Shared->LastSharedWake->Next = &SharedWake;
            }

            Shared->SharedCount++;
            Shared->LastSharedWake = &SharedWake;

            RtlpReleaseWaitBlockLock(SRWLock);

            RtlpAcquireSRWLockSharedWait(SRWLock, FirstWait, &SharedWake);

            // Successfully incremented the shared count, we acquired the lock
            break;
          }
        } else {
          SharedWake.Next = NULL;
          SharedWake.Wake = 0;

          // We need to setup the first wait block. Currently an exclusive lock
          // is held, change the lock to contended mode.
          StackWaitBlock.Exclusive = FALSE;
          StackWaitBlock.SharedCount = 1;
          StackWaitBlock.Next = NULL;
          StackWaitBlock.Last = &StackWaitBlock;
          StackWaitBlock.SharedWakeChain = &SharedWake;
          StackWaitBlock.LastSharedWake = &SharedWake;

          NewValue = (ULONG_PTR)&StackWaitBlock | RTL_SRWLOCK_OWNED |
                     RTL_SRWLOCK_CONTENDED;
          if ((LONG_PTR)InterlockedCompareExchangePointer(
                  &SRWLock->Ptr, (PVOID)NewValue, (PVOID)CurrentValue) ==
              CurrentValue) {
            RtlpAcquireSRWLockSharedWait(SRWLock, &StackWaitBlock, &SharedWake);

            // Successfully set the shared count, we acquired the lock
            break;
          }
        }
      } else {
        // This is a fast path, we can simply try to set the shared count to 1
        NewValue =
            (1 << RTL_SRWLOCK_BITS) | RTL_SRWLOCK_SHARED | RTL_SRWLOCK_OWNED;

        // The RTL_SRWLOCK_CONTENDED bit should never be set if neither the
        // RTL_SRWLOCK_SHARED nor the RTL_SRWLOCK_OWNED bit is set
        assert(!(CurrentValue & RTL_SRWLOCK_CONTENDED));

        if ((LONG_PTR)InterlockedCompareExchangePointer(
                &SRWLock->Ptr, (PVOID)NewValue, (PVOID)CurrentValue) ==
            CurrentValue) {
          // Successfully set the shared count, we acquired the lock
          break;
        }
      }
    }

    YieldProcessor();
  }
}

__declspec(noinline) VOID NTAPI
    RtlReleaseSRWLockShared(PRTL_SRWLOCK SRWLock) {
  LONG_PTR CurrentValue, NewValue;
  PRTLP_SRWLOCK_WAITBLOCK WaitBlock;
  BOOLEAN LastShared;

  while (1) {
    CurrentValue = *(volatile LONG_PTR *)&SRWLock->Ptr;

    if (CurrentValue & RTL_SRWLOCK_SHARED) {
      if (CurrentValue & RTL_SRWLOCK_CONTENDED) {
        // There's a wait block, we need to wake a pending
        // exclusive acquirer if this is the last shared release
        WaitBlock = RtlpAcquireWaitBlockLock(SRWLock);
        if (WaitBlock != NULL) {
          LastShared = (--WaitBlock->SharedCount == 0);

          if (LastShared)
            RtlpReleaseWaitBlockLockLastShared(SRWLock, WaitBlock);
          else
            RtlpReleaseWaitBlockLock(SRWLock);

          // We released the lock
          break;
        }
      } else {
        // This is a fast path, we can simply decrement the shared
        // count and store the pointer
        NewValue = CurrentValue >> RTL_SRWLOCK_BITS;

        if (--NewValue != 0) {
          NewValue = (NewValue << RTL_SRWLOCK_BITS) | RTL_SRWLOCK_SHARED |
                     RTL_SRWLOCK_OWNED;
        }

        if ((LONG_PTR)InterlockedCompareExchangePointer(
                &SRWLock->Ptr, (PVOID)NewValue, (PVOID)CurrentValue) ==
            CurrentValue) {
          // Successfully released the lock
          break;
        }
      }
    } else {
      // The RTL_SRWLOCK_SHARED bit has to be present now,
      // even in the contended case!
      RtlRaiseStatus(STATUS_RESOURCE_NOT_OWNED);
    }

    YieldProcessor();
  }
}


__declspec(noinline) VOID NTAPI
    RtlAcquireSRWLockExclusive(PRTL_SRWLOCK SRWLock) {
  __declspec(align(16)) RTLP_SRWLOCK_WAITBLOCK StackWaitBlock;
  PRTLP_SRWLOCK_WAITBLOCK First, Last;

  if (InterlockedBitTestAndSetPointer(&SRWLock->Ptr, RTL_SRWLOCK_OWNED_BIT)) {
    LONG_PTR CurrentValue, NewValue;

    while (1) {
      CurrentValue = *(volatile LONG_PTR *)&SRWLock->Ptr;

      if (CurrentValue & RTL_SRWLOCK_SHARED) {
        // A shared lock is being held right now. We need to add a wait block!

        if (CurrentValue & RTL_SRWLOCK_CONTENDED) {
          goto AddWaitBlock;
        } else {
          // There are no wait blocks so far, we need to add ourselves as the
          // first wait block. We need to keep the shared count!
          StackWaitBlock.Exclusive = TRUE;
          StackWaitBlock.SharedCount = (LONG)(CurrentValue >> RTL_SRWLOCK_BITS);
          StackWaitBlock.Next = NULL;
          StackWaitBlock.Last = &StackWaitBlock;
          StackWaitBlock.Wake = 0;

          NewValue = (ULONG_PTR)&StackWaitBlock | RTL_SRWLOCK_SHARED |
                     RTL_SRWLOCK_CONTENDED | RTL_SRWLOCK_OWNED;
          
          if ((LONG_PTR)InterlockedCompareExchangePointer(
                  &SRWLock->Ptr, (PVOID)NewValue, (PVOID)CurrentValue) ==
              CurrentValue) {
            RtlpAcquireSRWLockExclusiveWait(SRWLock, &StackWaitBlock);

            // Successfully acquired the exclusive lock
            break;
          }
        }
      } else {
        if (CurrentValue & RTL_SRWLOCK_OWNED) {
          // An exclusive lock is being held right now. We need to add a wait
          // block!

          if (CurrentValue & RTL_SRWLOCK_CONTENDED) {
          AddWaitBlock:
            StackWaitBlock.Exclusive = TRUE;
            StackWaitBlock.SharedCount = 0;
            StackWaitBlock.Next = NULL;
            StackWaitBlock.Last = &StackWaitBlock;
            StackWaitBlock.Wake = 0;

            First = RtlpAcquireWaitBlockLock(SRWLock);
            if (First != NULL) {
              Last = First->Last;
              Last->Next = &StackWaitBlock;
              First->Last = &StackWaitBlock;

              RtlpReleaseWaitBlockLock(SRWLock);

              RtlpAcquireSRWLockExclusiveWait(SRWLock, &StackWaitBlock);

              // Successfully acquired the exclusive lock
              break;
            }
          } else {
            // There are no wait blocks so far, we need to add ourselves as the
            // first wait block. We need to keep the shared count!
            StackWaitBlock.Exclusive = TRUE;
            StackWaitBlock.SharedCount = 0;
            StackWaitBlock.Next = NULL;
            StackWaitBlock.Last = &StackWaitBlock;
            StackWaitBlock.Wake = 0;

            NewValue = (ULONG_PTR)&StackWaitBlock | RTL_SRWLOCK_OWNED |
                       RTL_SRWLOCK_CONTENDED;
            if ((LONG_PTR)InterlockedCompareExchangePointer(
                    &SRWLock->Ptr, (PVOID)NewValue, (PVOID)CurrentValue) ==
                CurrentValue) {
              RtlpAcquireSRWLockExclusiveWait(SRWLock, &StackWaitBlock);

              // Successfully acquired the exclusive lock
              break;
            }
          }
        } else {
          if (!InterlockedBitTestAndSetPointer(&SRWLock->Ptr,
                                               RTL_SRWLOCK_OWNED_BIT)) {
            // We managed to get hold of a simple exclusive lock!
            break;
          }
        }
      }

      YieldProcessor();
    }
  }
}


__declspec(noinline) VOID NTAPI
    RtlReleaseSRWLockExclusive(PRTL_SRWLOCK SRWLock) {
  LONG_PTR CurrentValue, NewValue;
  PRTLP_SRWLOCK_WAITBLOCK WaitBlock;

  while (1) {
    CurrentValue = *(volatile LONG_PTR *)&SRWLock->Ptr;

    if (!(CurrentValue & RTL_SRWLOCK_OWNED)) {
      RtlRaiseStatus(STATUS_RESOURCE_NOT_OWNED);
    }

    if (!(CurrentValue & RTL_SRWLOCK_SHARED)) {
      if (CurrentValue & RTL_SRWLOCK_CONTENDED) {
        // There's a wait block, we need to wake the next pending
        //   acquirer (exclusive or shared)
        WaitBlock = RtlpAcquireWaitBlockLock(SRWLock);
        if (WaitBlock != NULL) {
          RtlpReleaseWaitBlockLockExclusive(SRWLock, WaitBlock);

          // We released the lock
          break;
        }
      } else {
        // This is a fast path, we can simply clear the RTL_SRWLOCK_OWNED
        // bit. All other bits should be 0 now because this is a simple
        //  exclusive lock and no one is waiting.

        assert(!(CurrentValue & ~RTL_SRWLOCK_OWNED));

        NewValue = 0;
        if ((LONG_PTR)InterlockedCompareExchangePointer(
                &SRWLock->Ptr, (PVOID)NewValue, (PVOID)CurrentValue) ==
            CurrentValue) {
          // We released the lock
          break;
        }
      }
    } else {
      // The RTL_SRWLOCK_SHARED bit must not be present now,
      //   not even in the contended case!
      RtlRaiseStatus(STATUS_RESOURCE_NOT_OWNED);
    }

    YieldProcessor();
  }
}




__declspec(noinline) BOOLEAN NTAPI
    RtlTryAcquireSRWLockExclusive(PRTL_SRWLOCK SRWLock) {
  return InterlockedCompareExchangePointer(
             &SRWLock->Ptr, (ULONG_PTR *)RTL_SRWLOCK_OWNED, 0) == 0;
}







__declspec(noinline) BOOLEAN NTAPI
    RtlTryAcquireSRWLockShared(PRTL_SRWLOCK SRWLock) {

  LONG_PTR CompareValue, NewValue, GotValue;

  do {
    CompareValue = *(volatile LONG_PTR *)&SRWLock->Ptr;
    NewValue = ((CompareValue >> RTL_SRWLOCK_BITS) + 1) | RTL_SRWLOCK_SHARED |
               RTL_SRWLOCK_OWNED;

    // Only increment shared count if there is no waiter
    CompareValue &= ~RTL_SRWLOCK_MASK | RTL_SRWLOCK_SHARED | RTL_SRWLOCK_OWNED;
  } while (((GotValue = (LONG_PTR)InterlockedCompareExchangePointer(
                 &SRWLock->Ptr, (LONG_PTR *)NewValue,
                 (LONG_PTR *)CompareValue)) != CompareValue) &&
           (((GotValue & RTL_SRWLOCK_MASK) ==
             (RTL_SRWLOCK_SHARED | RTL_SRWLOCK_OWNED)) ||
            (GotValue == 0)));

  return ((GotValue & RTL_SRWLOCK_MASK) ==
          (RTL_SRWLOCK_SHARED | RTL_SRWLOCK_OWNED)) ||
         (GotValue == 0);
}