#include "call.h"
#include "interop.h"
#include "utilities.h"
#include "state.h"
#include "value.h"
#include "environment.h"
#include "closure.h"
#include "promise.h"
#include "language.h"

/********************************************************************************
 * definition
 *******************************************************************************/

struct instrumentr_call_impl_t {
    struct instrumentr_model_impl_t model;
    instrumentr_value_t function;
    instrumentr_language_t expression;
    instrumentr_value_t arguments;
    instrumentr_environment_t environment;
    int active;
    instrumentr_value_t result;
};

/********************************************************************************
 * finalize
 *******************************************************************************/

void instrumentr_call_finalize(instrumentr_model_t model) {
    instrumentr_call_t call = (instrumentr_call_t)(model);

    instrumentr_value_release(call->function);
    call->function = NULL;

    instrumentr_language_release(call->expression);
    call->expression = NULL;

    instrumentr_value_release(call->arguments);
    call->arguments = NULL;

    instrumentr_environment_release(call->environment);
    call->environment = NULL;

    if (call->result != NULL) {
        instrumentr_value_release(call->result);
        call->result = NULL;
    }
}

/********************************************************************************
 * create
 *******************************************************************************/

const char* unwrap_name(SEXP r_name) {
    const char* name = NULL;

    if (TYPEOF(r_name) == SYMSXP) {
        name = R_CHAR(PRINTNAME(r_name));
    }

    return name;
}

void mark_argument_promises(instrumentr_state_t state,
                            instrumentr_call_t call,
                            SEXP r_closure,
                            SEXP r_environment) {
    for (SEXP r_params = FORMALS(r_closure); r_params != R_NilValue;
         r_params = CDR(r_params)) {
        SEXP r_argname = TAG(r_params);

        SEXP r_argval = Rf_findVarInFrame(r_environment, r_argname);

        if (TYPEOF(r_argval) == PROMSXP) {
            instrumentr_value_t value =
                instrumentr_state_value_table_lookup(state, r_argval, 1);
            instrumentr_promise_t promise = instrumentr_value_as_promise(value);
            instrumentr_promise_make_argument(promise, call);
        }
    }
}

instrumentr_call_t instrumentr_call_create(instrumentr_state_t state,
                                           instrumentr_value_t function,
                                           SEXP r_expression,
                                           SEXP r_arguments,
                                           SEXP r_environment) {
    instrumentr_model_t model =
        instrumentr_model_create(state,
                                 sizeof(struct instrumentr_call_impl_t),
                                 INSTRUMENTR_MODEL_TYPE_CALL,
                                 instrumentr_call_finalize,
                                 INSTRUMENTR_ORIGIN_LOCAL);

    instrumentr_call_t call = (instrumentr_call_t)(model);

    call->function = function;
    instrumentr_value_acquire(call->function);

    call->expression = instrumentr_value_as_language(
        instrumentr_state_value_table_lookup(state, r_expression, 1));
    instrumentr_language_acquire(call->expression);

    call->arguments =
        instrumentr_state_value_table_lookup(state, r_arguments, 1);
    instrumentr_value_acquire(call->arguments);

    call->environment = instrumentr_state_value_table_lookup_environment(
        state, r_environment, 1);
    instrumentr_environment_acquire(call->environment);

    if (instrumentr_value_is_closure(function)) {
        instrumentr_closure_t closure = instrumentr_value_as_closure(function);
        SEXP r_closure = instrumentr_closure_get_sexp(closure);
        mark_argument_promises(state, call, r_closure, r_environment);
    }

    call->result = NULL;

    return call;
}

/********************************************************************************
 * interop
 *******************************************************************************/

INSTRUMENTR_MODEL_DEFINE_DERIVED_API(INSTRUMENTR_MODEL_TYPE_CALL, call, call)

/********************************************************************************
 * function
 *******************************************************************************/

/* accessor  */
instrumentr_value_t instrumentr_call_get_function(instrumentr_call_t call) {
    return call->function;
}

SEXP r_instrumentr_call_get_function(SEXP r_call) {
    instrumentr_call_t call = instrumentr_call_unwrap(r_call);
    instrumentr_value_t function = instrumentr_call_get_function(call);
    return instrumentr_value_wrap(function);
}

/********************************************************************************
 * expression
 *******************************************************************************/

/* accessor  */
instrumentr_language_t
instrumentr_call_get_expression(instrumentr_call_t call) {
    return call->expression;
}

SEXP r_instrumentr_call_get_expression(SEXP r_call) {
    instrumentr_call_t call = instrumentr_call_unwrap(r_call);
    instrumentr_language_t language = instrumentr_call_get_expression(call);
    return instrumentr_language_wrap(language);
}

/********************************************************************************
 * arguments
 *******************************************************************************/

/* accessor  */
instrumentr_value_t instrumentr_call_get_arguments(instrumentr_call_t call) {
    return call->arguments;
}

SEXP r_instrumentr_call_get_arguments(SEXP r_call) {
    instrumentr_call_t call = instrumentr_call_unwrap(r_call);
    instrumentr_value_t value = instrumentr_call_get_arguments(call);
    return instrumentr_value_wrap(value);
}

/********************************************************************************
 * environment
 *******************************************************************************/

/* accessor  */
instrumentr_environment_t
instrumentr_call_get_environment(instrumentr_call_t call) {
    return call->environment;
}

SEXP r_instrumentr_call_get_environment(SEXP r_call) {
    instrumentr_call_t call = instrumentr_call_unwrap(r_call);
    instrumentr_environment_t environment =
        instrumentr_call_get_environment(call);
    return instrumentr_environment_wrap(environment);
}

/********************************************************************************
 * active
 *******************************************************************************/

/* accessor  */
int instrumentr_call_is_active(instrumentr_call_t call) {
    return call->active;
}

SEXP r_instrumentr_call_is_active(SEXP r_call) {
    instrumentr_call_t call = instrumentr_call_unwrap(r_call);
    int active = instrumentr_call_is_active(call);
    return instrumentr_c_int_to_r_logical(active);
}

/* mutator  */
void instrumentr_call_activate(instrumentr_call_t call) {
    call->active = 1;
}

/* mutator  */
void instrumentr_call_deactivate(instrumentr_call_t call) {
    call->active = 0;
}

/********************************************************************************
 * result
 *******************************************************************************/

/* accessor  */
int instrumentr_call_has_result(instrumentr_call_t call) {
    return call->result != NULL;
}

SEXP r_instrumentr_call_has_result(SEXP r_call) {
    instrumentr_call_t call = instrumentr_call_unwrap(r_call);
    int result = instrumentr_call_has_result(call);
    return instrumentr_c_int_to_r_logical(result);
}

/* accessor  */
instrumentr_value_t instrumentr_call_get_result(instrumentr_call_t call) {
    if (instrumentr_call_has_result(call)) {
        return call->result;
    } else {
        instrumentr_log_error("call does not have a result");
        /* NOTE: never executed*/
        return NULL;
    }
}

SEXP r_instrumentr_call_get_result(SEXP r_call) {
    instrumentr_call_t call = instrumentr_call_unwrap(r_call);
    instrumentr_value_t result = instrumentr_call_get_result(call);
    return instrumentr_value_wrap(result);
}

/* mutator */
void instrumentr_call_set_result(instrumentr_call_t call,
                                 instrumentr_value_t result) {
    call->result = result;
    instrumentr_value_acquire(result);
}
