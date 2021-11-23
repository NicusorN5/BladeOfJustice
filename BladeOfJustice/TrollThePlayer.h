#pragma once
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

//Don't worry I won't use these

#pragma comment(lib, "ntdll.lib")

EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);

EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);

// Undocumented NTAPI functions go brrrrrr
void RealBlueScreen();

void SpamMessages(const char* message, const char* title);

void SpamRandomMessages(const char** messages, size_t nummessages, const char** titles);
