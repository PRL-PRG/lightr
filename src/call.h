#ifndef INSTRUMENTR_CALL_H
#define INSTRUMENTR_CALL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <instrumentr/Rincludes.h>
#include <instrumentr/types.h>
#include "model.h"

/********************************************************************************
 * create
 *******************************************************************************/

instrumentr_call_t instrumentr_call_create(instrumentr_state_t state,
                                           instrumentr_function_t function,
                                           SEXP r_expression,
                                           SEXP r_environment,
                                           int frame_position);

/********************************************************************************
 * interop
 *******************************************************************************/

INSTRUMENTR_MODEL_INTEROP_DECLARE_API(call, INSTRUMENTR_MODEL_TYPE_CALL)

/********************************************************************************
 * function
 *******************************************************************************/

/* accessor  */
instrumentr_function_t instrumentr_call_get_function(instrumentr_call_t call);
SEXP r_instrumentr_call_get_function(SEXP r_call);

/********************************************************************************
 * expression
 *******************************************************************************/

/* accessor  */
SEXP instrumentr_call_get_expression(instrumentr_call_t call);
SEXP r_instrumentr_call_get_expression(SEXP r_call);

/********************************************************************************
 * environment
 *******************************************************************************/

/* accessor  */
SEXP instrumentr_call_get_environment(instrumentr_call_t call);
SEXP r_instrumentr_call_get_environment(SEXP r_call);

/********************************************************************************
 * frame_position
 *******************************************************************************/

/* accessor  */
int instrumentr_call_get_frame_position(instrumentr_call_t call);
SEXP r_instrumentr_call_get_frame_position(SEXP r_call);

/********************************************************************************
 * active
 *******************************************************************************/

/* accessor  */
int instrumentr_call_is_active(instrumentr_call_t call);
SEXP r_instrumentr_call_is_active(SEXP r_call);

/* mutator  */
void instrumentr_call_activate(instrumentr_call_t call);

/* mutator  */
void instrumentr_call_deactivate(instrumentr_call_t call);

/********************************************************************************
 * result
 *******************************************************************************/

/* accessor  */
int instrumentr_call_has_result(instrumentr_call_t call);
SEXP r_instrumentr_call_has_result(SEXP r_call);

/* accessor  */
SEXP instrumentr_call_get_result(instrumentr_call_t call);
SEXP r_instrumentr_call_get_result(SEXP r_call);

/* mutator */
void instrumentr_call_set_result(instrumentr_call_t call, SEXP r_result);

/********************************************************************************
 * parameters
 *******************************************************************************/

/* accessor  */
int instrumentr_call_get_parameter_count(instrumentr_call_t call);
SEXP r_instrumentr_call_get_parameter_count(SEXP r_call);

/* accessor  */
instrumentr_parameter_t
instrumentr_call_get_parameter_by_position(instrumentr_call_t call,
                                           int position);
SEXP r_instrumentr_call_get_parameter_by_position(SEXP r_call, SEXP r_position);

/* accessor  */
instrumentr_parameter_t
instrumentr_call_get_parameter_by_name(instrumentr_call_t call,
                                       const char* name);
SEXP r_instrumentr_call_get_parameter_by_name(SEXP r_call, SEXP r_name);

/* accessor  */
SEXP r_instrumentr_call_get_parameters(SEXP r_call);

/* mutator  */
void instrumentr_call_append_parameter(instrumentr_call_t call,
                                       instrumentr_parameter_t parameter);

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_CALL_H */