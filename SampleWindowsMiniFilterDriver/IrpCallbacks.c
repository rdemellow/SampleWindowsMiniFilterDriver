#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>

#include "Debug.h"
#include "IrpCallbacks.h"

extern ULONG gTraceFlags;

//MiniFilter callback routines.

_Use_decl_annotations_
FLT_PREOP_CALLBACK_STATUS SampleFsPreCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID *CompletionContext)
{

    UNREFERENCED_PARAMETER(Data);
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("SampleWindowsMiniFilterDriver!SampleFsPreCreate: Entered\n"));

    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}

_Use_decl_annotations_
FLT_POSTOP_CALLBACK_STATUS SampleFsPostCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID CompletionContext, FLT_POST_OPERATION_FLAGS Flags)
{
    UNREFERENCED_PARAMETER(Data);
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);
    UNREFERENCED_PARAMETER(Flags);

    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("SampleWindowsMiniFilterDriver!SampleFsPostCreate: Entered\n"));

    return FLT_POSTOP_FINISHED_PROCESSING;
}

