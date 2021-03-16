#ifndef INSTRUMENTR_TRACER_H
#define INSTRUMENTR_TRACER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <instrumentr/Rincludes.h>
#include <instrumentr/types.h>
#include "event.h"
#include "object.h"

/********************************************************************************
 * create
 *******************************************************************************/

instrumentr_tracer_t instrumentr_tracer_create();

SEXP r_instrumentr_tracer_create();

/********************************************************************************
 * finalize tracing
 *******************************************************************************/

SEXP instrumentr_tracer_finalize_tracing(instrumentr_tracer_t tracer);

/********************************************************************************
 * clear
 *******************************************************************************/

void instrumentr_tracer_clear(instrumentr_tracer_t tracer);

/********************************************************************************
 * interop
 *******************************************************************************/

INSTRUMENTR_OBJECT_INTEROP_DECLARE_API(tracer, INSTRUMENTR_OBJECT_TYPE_TRACER)

/********************************************************************************
 * reset
 *******************************************************************************/

void instrumentr_tracer_reset(instrumentr_tracer_t tracer);

/********************************************************************************
 * dyntracer
 *******************************************************************************/

dyntracer_t* instrumentr_tracer_get_dyntracer(instrumentr_tracer_t tracer);

/********************************************************************************
 * state
 *******************************************************************************/

/*  accessor  */
instrumentr_state_t instrumentr_tracer_get_state(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_get_state(SEXP r_tracer);

/********************************************************************************
 * application
 *******************************************************************************/

/*  accessor  */
instrumentr_application_t
instrumentr_tracer_get_application(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_get_application(SEXP r_tracer);

/*  mutator  */
void instrumentr_tracer_set_application(instrumentr_tracer_t tracer,
                                        instrumentr_application_t application);

/*  mutator  */
void instrumentr_tracer_remove_application(instrumentr_tracer_t tracer);

/********************************************************************************
 * r_environment
 *******************************************************************************/

/*  accessor  */
SEXP instrumentr_tracer_get_environment(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_get_environment(SEXP r_tracer);

/********************************************************************************
 * active_callback
 *******************************************************************************/

/* accessor  */
int instrumentr_tracer_is_active(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_is_active(SEXP r_tracer);

/* accessor  */
instrumentr_callback_t
instrumentr_tracer_get_active_callback(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_get_active_callback(SEXP r_tracer);

/* mutator  */
void instrumentr_tracer_set_active_callback(instrumentr_tracer_t tracer,
                                            instrumentr_callback_t callback);

/* mutator  */
void instrumentr_tracer_unset_active_callback(instrumentr_tracer_t tracer);

/********************************************************************************
 * status
 *******************************************************************************/

/* accessor  */
int instrumentr_tracer_is_enabled(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_is_enabled(SEXP r_tracer);

/* mutator  */
void instrumentr_tracer_enable(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_enable(SEXP r_tracer);

/* mutator  */
void instrumentr_tracer_disable(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_disable(SEXP r_tracer);

/* mutator  */
void instrumentr_tracer_reinstate(instrumentr_tracer_t tracer);
SEXP r_instrumentr_tracer_reinstate(SEXP r_tracer);

/* mutator  */
void instrumentr_tracer_set_tracing_status(instrumentr_tracer_t tracer,
                                           int status);

/********************************************************************************
 * callback
 *******************************************************************************/

/* accessor */
int instrumentr_tracer_has_callback(instrumentr_tracer_t tracer,
                                    instrumentr_event_t event);

SEXP r_instrumentr_tracer_has_callback(SEXP r_tracer, SEXP r_event);

/* accessor */
instrumentr_callback_t
instrumentr_tracer_get_callback(instrumentr_tracer_t tracer,
                                instrumentr_event_t event);

SEXP r_instrumentr_tracer_get_callback(SEXP r_tracer, SEXP r_event);

/* accessor */
void instrumentr_tracer_set_callback(instrumentr_tracer_t tracer,
                                     instrumentr_callback_t callback);

SEXP r_instrumentr_tracer_set_callback(SEXP r_tracer, SEXP r_callback);

/* mutator */
void instrumentr_tracer_remove_callback(instrumentr_tracer_t tracer,
                                        instrumentr_event_t event);

SEXP r_instrumentr_tracer_remove_callback(SEXP r_tracer, SEXP r_event);

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_TRACER_H */