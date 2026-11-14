#include "common_types.h"
#include "imports.h"

extern "C" {
__declspec(dllimport) DWORD __stdcall GetCurrentThreadId(void);
__declspec(dllimport) void *__stdcall GetCurrentThread(void);
__declspec(dllimport) int __stdcall DuplicateHandle(void *, void *, void *, void **, DWORD, int, DWORD);
__declspec(dllimport) DWORD __stdcall TlsAlloc(void);
__declspec(dllimport) void *__stdcall TlsGetValue(DWORD);
__declspec(dllimport) int __stdcall TlsSetValue(DWORD, void *);
__declspec(dllimport) void *__stdcall CreateEventA(void *, int, int, const char *);
__declspec(dllimport) int __stdcall SetEvent(void *);
__declspec(dllimport) int __stdcall ResetEvent(void *);
__declspec(dllimport) DWORD __stdcall WaitForSingleObject(void *, DWORD);
__declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD, void *const *, int, DWORD);
__declspec(dllimport) void *__stdcall CreateThread(void *, DWORD, DWORD(__stdcall *)(void *), void *, DWORD, DWORD *);
__declspec(dllimport) DWORD __stdcall SuspendThread(void *);
__declspec(dllimport) DWORD __stdcall ResumeThread(void *);
__declspec(dllimport) long __stdcall InterlockedExchange(long volatile *, long);
}

extern void Com_InitThreadData(int index);

/*
 1.3 keeps per-thread value tables behind one TLS slot. Layout and use are read from
 retail 1.3 0x462360-0x462660 (PINNED by disassembly); the original function and
 variable names are unknown.
*/
// real names unknown; names picked so /GL bss order matches retail 0xd528a4..f4
void *wt_eventA15;
void *wt_eventB11;
volatile long wt_flag10;
void *wt_values016[5];
void *wt_values124[5];
// retail 0xd528d8, spans 12 B: next object is at 0xd528e4
DWORD wt_threadId13[3];
void *wt_handle23[2];
void *wt_eventC28;
DWORD wt_tlsIndex25;
void *wt_eventD8;

void Sys_InitMainThread(void)
{
    void *proc = 0;
    void *self;

    wt_threadId13[0] = GetCurrentThreadId();
    self = GetCurrentThread();
    // retail passes the address of a zeroed local as the target process handle
    DuplicateHandle(proc, self, &proc, &wt_handle23[0], 0, 0, 0);
    wt_tlsIndex25 = TlsAlloc();
    TlsSetValue(wt_tlsIndex25, wt_values016);
    Com_InitThreadData(0);
}

// retail 0x4623c0, name unknown
static DWORD __stdcall Sys_ThreadMain(void *arg)
{
    TlsSetValue(wt_tlsIndex25, wt_values124);
    Com_InitThreadData(1);
    ((void (*)(void))arg)();
    return 0;
}

// retail 0x4623f0, name unknown
Bool Sys_CreateThread_4623f0(void (*threadMain)(void))
{
    wt_eventC28 = CreateEventA(0, 0, 0, 0);
    wt_eventD8 = CreateEventA(0, 1, 1, 0);
    wt_eventA15 = CreateEventA(0, 1, 0, 0);
    wt_eventB11 = CreateEventA(0, 0, 0, 0);
    wt_handle23[1] = CreateThread(0, 0, Sys_ThreadMain, (void *)threadMain, 4, &wt_threadId13[1]);
    return wt_handle23[1] != 0;
}

// retail 0x462460, name unknown
void Sys_ResumeThread_462460(int index)
{
    ResumeThread(wt_handle23[index]);
}

// retail 0x462480, name unknown
long Sys_ClearFlag_462480(void)
{
    return InterlockedExchange(&wt_flag10, 0);
}

// retail 0x462490, name unknown
void Sys_SetEventD_462490(void)
{
    SetEvent(wt_eventD8);
}

// retail 0x4624a0, name unknown
void Sys_Handshake_4624a0(void)
{
    if (WaitForSingleObject(wt_eventA15, 0) != 0x102) {
        ResetEvent(wt_eventA15);
        SetEvent(wt_eventB11);
        WaitForSingleObject(wt_eventC28, 0xFFFFFFFF);
    }
}

// retail 0x4624e0, name unknown
void Sys_WaitEventD_4624e0(void)
{
    WaitForSingleObject(wt_eventD8, 0xFFFFFFFF);
}

// retail 0x4624f0, name unknown
void Sys_SignalB_4624f0(int value)
{
    ResetEvent(wt_eventD8);
    wt_flag10 = value;
    SetEvent(wt_eventB11);
}

// retail 0x462520, name unknown
int Sys_EventAPending_462520(void)
{
    return WaitForSingleObject(wt_eventA15, 0) == 0x102;
}

// retail 0x462540, name unknown
void Sys_SignalCWaitA_462540(void)
{
    SetEvent(wt_eventC28);
    WaitForSingleObject(wt_eventA15, 0xFFFFFFFF);
}

// retail 0x462560, name unknown
int Sys_IsSecondThread_462560(void)
{
    return GetCurrentThreadId() == wt_threadId13[1];
}

int Sys_IsMainThread(void)
{
    return GetCurrentThreadId() == wt_threadId13[0];
}

void Sys_SetValue(int valueIndex, void *data)
{
    ((void **)TlsGetValue(wt_tlsIndex25))[valueIndex] = data;
}

void *Sys_GetValue(int valueIndex)
{
    void **values = (void **)TlsGetValue(wt_tlsIndex25);
    return values[valueIndex];
}

// retail 0x4625e0, name unknown
void Sys_WaitEventB_4625e0(void)
{
    WaitForMultipleObjects(1, &wt_eventB11, 0, 0xFFFFFFFF);
}

// retail 0x462600, name unknown
void Sys_SuspendOtherThreads_462600(void)
{
    DWORD cur = GetCurrentThreadId();
    int i;

    for (i = 0; i < 2; i++) {
        if (wt_handle23[i] && wt_threadId13[i] && wt_threadId13[i] != cur)
            SuspendThread(wt_handle23[i]);
    }
}

// retail 0x462640, name unknown
void Sys_SetEventA_462640(void)
{
    SetEvent(wt_eventA15);
}

Bool Sys_ReturnFalse(void)
{
    return 0;
}

// retail 0x462660, empty and unreferenced; name unknown
Bool Sys_ReturnFalse_462660(void)
{
    return 0;
}
