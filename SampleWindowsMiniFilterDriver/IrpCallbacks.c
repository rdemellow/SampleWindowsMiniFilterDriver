#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>
#include <Ntifs.h>

#include "Debug.h"
#include "IrpCallbacks.h"

extern ULONG gTraceFlags;

DECLARE_CONST_UNICODE_STRING(gfooFileName, L"foo.txt");
DECLARE_CONST_UNICODE_STRING(gBarFileName, L"bar.txt");

//MiniFilter callback routines.

_Use_decl_annotations_
FLT_PREOP_CALLBACK_STATUS SampleFsPreCreate(PFLT_CALLBACK_DATA Data, PCFLT_RELATED_OBJECTS FltObjects, PVOID *CompletionContext)
{
    PAGED_CODE();
    UNREFERENCED_PARAMETER(Data);
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(CompletionContext);

    PT_DBG_PRINT(PTDBG_TRACE_ROUTINES, ("SampleWindowsMiniFilterDriver!SampleFsPreCreate: Entered\n"));

    FLT_PREOP_CALLBACK_STATUS callbackStatus = FLT_PREOP_SUCCESS_WITH_CALLBACK;

    PFLT_FILE_NAME_INFORMATION pFileInfo = NULL;
    NTSTATUS status = FltGetFileNameInformation(Data, FLT_FILE_NAME_OPENED | FLT_FILE_NAME_QUERY_FILESYSTEM_ONLY, &pFileInfo);
    if (NT_SUCCESS(status))
    {
        status = FltParseFileNameInformation(pFileInfo);
        if (RtlCompareUnicodeString(&pFileInfo->FinalComponent, &gfooFileName, FALSE) == 0)
        {
            DbgBreakPoint();
            UNICODE_STRING newFileName = { 0 };
            newFileName.Buffer = ExAllocatePoolWithTag(NonPagedPool, pFileInfo->Name.Length, 'SmFs');
            newFileName.MaximumLength = pFileInfo->Name.Length;
            if (newFileName.Buffer)
            {
                RtlCopyUnicodeString(&newFileName, &pFileInfo->Volume);
                status = RtlAppendUnicodeStringToString(&newFileName, &pFileInfo->ParentDir);
                if (NT_SUCCESS(status))
                {
                    status = RtlAppendUnicodeStringToString(&newFileName, &gBarFileName);
                    if (NT_SUCCESS(status))
                    {
                        status = IoReplaceFileObjectName(FltObjects->FileObject, newFileName.Buffer, newFileName.Length);
                        if (NT_SUCCESS(status))
                        {
                            Data->IoStatus.Status = STATUS_REPARSE;
                            Data->IoStatus.Information = IO_REPARSE;
                            callbackStatus = FLT_PREOP_COMPLETE;
                            FltIsCallbackDataDirty(Data);
                        }
                    }
                }
                ExFreePoolWithTag(newFileName.Buffer, 'SmFs');
            }
        }
    }

    return callbackStatus;
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

