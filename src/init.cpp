#include <instrumentr/api.h>
#include "instrumentr_internals.h"
#include "trace.h"
#include "object.h"
#include "tracer.h"
#include "application.h"
#include "environment.h"
#include "function.h"
#include "call.h"
#include "parameter.h"
#include "argument.h"
#include "call_stack.h"
#include "callback.h"
#include "context.h"
#include "interop.h"
#include "state.h"
#include "promise.h"
#include "value.h"
#include "exec_stats.h"
#include "frame.h"
#include "utilities.h"
#include "alloc_stats.h"
#include "integer.h"
#include "real.h"
#include "logical.h"
#include "complex.h"
#include "raw.h"

#include <R_ext/Rdynload.h>

#include <stdio.h>

#define DECLARE_BINDING(NAME, PARAMETERS) \
    { #NAME, (DL_FUNC) &NAME, PARAMETERS }

#define DECLARE_API_BINDING(NAME, OUTPUT_TYPE, ...) \
    {#NAME, (DL_FUNC) &NAME, PP_NARG(__VA_ARGS__)},

#ifdef __cplusplus
extern "C" {
#endif

const R_CallMethodDef CallEntries[] = {

    /* instrumentr */
    DECLARE_BINDING(r_instrumentr_get_commit_hash, 0),
    DECLARE_BINDING(r_instrumentr_is_tracing_enabled, 0),
    DECLARE_BINDING(r_instrumentr_disable_tracing, 0),
    DECLARE_BINDING(r_instrumentr_enable_tracing, 0),
    DECLARE_BINDING(r_instrumentr_reinstate_tracing, 0),
    DECLARE_BINDING(r_instrumentr_initialize, 2),
    DECLARE_BINDING(r_instrumentr_finalize, 0),
    DECLARE_BINDING(r_instrumentr_initialize_tracing, 1),
    DECLARE_BINDING(r_instrumentr_finalize_tracing, 1),

    /* trace */
    DECLARE_BINDING(r_instrumentr_trace_code, 3),
    DECLARE_BINDING(r_instrumentr_trace_tracing_entry, 4),
    DECLARE_BINDING(r_instrumentr_trace_tracing_exit, 1),
    DECLARE_BINDING(r_instrumentr_trace_package_load, 2),
    DECLARE_BINDING(r_instrumentr_trace_package_unload, 2),
    DECLARE_BINDING(r_instrumentr_trace_package_attach, 2),
    DECLARE_BINDING(r_instrumentr_trace_package_detach, 2),

    INSTRUMENTR_R_API_MAP(DECLARE_API_BINDING)

        {NULL, NULL, 0}};

void R_init_instrumentr(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    INSTRUMENTR_EXPORT_API()
}

void R_unload_instrumentr(DllInfo* info) {
}

#ifdef __cplusplus
}
#endif
