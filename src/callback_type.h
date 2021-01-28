#ifndef INSTRUMENTR_CALLBACK_TYPE_H
#define INSTRUMENTR_CALLBACK_TYPE_H

#include <instrumentr/types.h>

typedef enum {
    INSTRUMENTR_CALLBACK_TRACING_ENTRY = 0,
    INSTRUMENTR_CALLBACK_TRACING_EXIT,
    INSTRUMENTR_CALLBACK_PACKAGE_LOAD,
    INSTRUMENTR_CALLBACK_PACKAGE_UNLOAD,
    INSTRUMENTR_CALLBACK_PACKAGE_ATTACH,
    INSTRUMENTR_CALLBACK_PACKAGE_DETACH,
    INSTRUMENTR_CALLBACK_BUILTIN_CALL_ENTRY,
    INSTRUMENTR_CALLBACK_BUILTIN_CALL_EXIT,
    INSTRUMENTR_CALLBACK_SPECIAL_CALL_ENTRY,
    INSTRUMENTR_CALLBACK_SPECIAL_CALL_EXIT,
    INSTRUMENTR_CALLBACK_CLOSURE_CALL_ENTRY,
    INSTRUMENTR_CALLBACK_CLOSURE_CALL_EXIT,
    INSTRUMENTR_CALLBACK_EVAL_ENTRY,
    INSTRUMENTR_CALLBACK_EVAL_EXIT,
    INSTRUMENTR_CALLBACK_GC_ALLOCATION,
    INSTRUMENTR_CALLBACK_VARIABLE_DEFINITION,
    INSTRUMENTR_CALLBACK_VARIABLE_ASSIGNMENT,
    INSTRUMENTR_CALLBACK_VARIABLE_REMOVAL,
    INSTRUMENTR_CALLBACK_VARIABLE_LOOKUP
} instrumentr_callback_type_t;

int instrumentr_callback_type_get_parameter_count(
    instrumentr_callback_type_t callback_type);

const char*
instrumentr_callback_type_get_name(instrumentr_callback_type_t callback_type);

#endif /* INSTRUMENTR_CALLBACK_TYPE_H */