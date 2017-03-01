#pragma once
#include <Windows.h>

#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#define ONEPAGESIZE 0x1000
#define STATUS_SUCCESS 0x00000000  

/* 此枚举用于配合NtQuerySystemInformation函数，其函数信息如下：
 *
 * Retrieves the specified system information.
 *		NTSTATUS WINAPI NtQuerySystemInformation(
 *		 _In_      SYSTEM_INFORMATION_CLASS SystemInformationClass,
 *		 _Inout_   PVOID                    SystemInformation,
 *		 _In_      ULONG                    SystemInformationLength,
 *		 _Out_opt_ PULONG                   ReturnLength
 *		);
 * MSDN注明：NtQuerySystemInformation may be altered or unavailable in future versions of Windows. Applications should use the alternate functions listed in this topic.
 * MSDN链接：https://msdn.microsoft.com/en-us/library/ms724509.aspx
 * 微软推荐，部分功能可使用新的函数代替
 */



typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,					// 0        Y        N
	SystemProcessorInformation,				// 1        Y        N
	SystemPerformanceInformation,			// 2        Y        N
	SystemTimeOfDayInformation,				// 3        Y        N
	SystemNotImplemented1,					// 4        Y        N
	SystemProcessesAndThreadsInformation,	// 5        Y        N
	SystemCallCounts,						// 6        Y        N
	SystemConfigurationInformation,			// 7        Y        N
	SystemProcessorTimes,					// 8        Y        N
	SystemGlobalFlag,						// 9        Y        Y
	SystemNotImplemented2,					// 10       Y        N
	SystemModuleInformation,				// 11       Y        N
	SystemLockInformation,					// 12       Y        N
	SystemNotImplemented3,					// 13       Y        N
	SystemNotImplemented4,					// 14       Y        N
	SystemNotImplemented5,					// 15       Y        N
	SystemHandleInformation,				// 16       Y        N
	SystemObjectInformation,				// 17       Y        N
	SystemPagefileInformation,				// 18       Y        N
	SystemInstructionEmulationCounts,		// 19       Y        N
	SystemInvalidInfoClass1,				// 20
	SystemCacheInformation,					// 21       Y        Y
	SystemPoolTagInformation,				// 22       Y        N
	SystemProcessorStatistics,				// 23       Y        N
	SystemDpcInformation,					// 24       Y        Y
	SystemNotImplemented6,					// 25       Y        N
	SystemLoadImage,						// 26       N        Y
	SystemUnloadImage,						// 27       N        Y
	SystemTimeAdjustment,					// 28       Y        Y
	SystemNotImplemented7,					// 29       Y        N
	SystemNotImplemented8,					// 30       Y        N
	SystemNotImplemented9,					// 31       Y        N
	SystemCrashDumpInformation,				// 32       Y        N
	SystemExceptionInformation,				// 33       Y        N
	SystemCrashDumpStateInformation,		// 34       Y        Y/N
	SystemKernelDebuggerInformation,		// 35       Y        N
	SystemContextSwitchInformation,			// 36       Y        N
	SystemRegistryQuotaInformation,			// 37       Y        Y
	SystemLoadAndCallImage,					// 38       N        Y
	SystemPrioritySeparation,				// 39       N        Y
	SystemNotImplemented10,					// 40       Y        N
	SystemNotImplemented11,					// 41       Y        N
	SystemInvalidInfoClass2,				// 42
	SystemInvalidInfoClass3,				// 43
	SystemTimeZoneInformation,				// 44       Y        N
	SystemLookasideInformation,				// 45       Y        N
	SystemSetTimeSlipEvent,					// 46       N        Y
	SystemCreateSession,					// 47       N        Y
	SystemDeleteSession,					// 48       N        Y
	SystemInvalidInfoClass4,				// 49
	SystemRangeStartInformation,			// 50       Y        N
	SystemVerifierInformation,				// 51       Y        Y
	SystemAddVerifier,						// 52       N        Y
	SystemSessionProcessesInformation		// 53       Y        N
} SYSTEM_INFORMATION_CLASS;




typedef NTSTATUS(NTAPI *_NtQuerySystemInformation)(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	OUT PULONG ReturnLength OPTIONAL
	);


typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO {
	ULONG ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;


typedef struct _SYSTEM_HANDLE_INFORMATION {
	ULONG HandleCount; /* Or NumberOfHandles if you prefer. */
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;


typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;



/*
 * 
 *
 *
 */
typedef struct _OBJECT_TYPE_INFORMATION {
	UNICODE_STRING TypeName;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccessMask;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	ULONG PoolType;
	ULONG DefaultPagedPoolCharge;
	ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;


typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} MOBJECT_NAME_INFORMATION, *PMOBJECT_NAME_INFORMATION;

typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectAllInformation,
	ObjectDataInformation
} OBJECT_INFORMATION_CLASS;


typedef NTSTATUS(NTAPI *_NtQueryObject)(
	_In_opt_ HANDLE Handle,
	_In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
	_Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
	_In_ ULONG ObjectInformationLength,
	_Out_opt_ PULONG ReturnLength
	);

