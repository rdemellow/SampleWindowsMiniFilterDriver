#pragma once

_IRQL_requires_max_(PASSIVE_LEVEL)
FLT_PREOP_CALLBACK_STATUS
SampleFsPreCreate(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID *CompletionContext
);

_IRQL_requires_max_(PASSIVE_LEVEL)
FLT_POSTOP_CALLBACK_STATUS
SampleFsPostCreate(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
);
