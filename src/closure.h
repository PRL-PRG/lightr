#ifndef INSTRUMENTR_CLOSURE_H
#define INSTRUMENTR_CLOSURE_H

#include <instrumentr/api.h>
#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * create
 *******************************************************************************/

instrumentr_closure_t instrumentr_closure_create(instrumentr_state_t state,
                                                 SEXP r_sexp);

/********************************************************************************
 * interop
 *******************************************************************************/

INSTRUMENTR_MODEL_INTEROP_DECLARE_API(closure, INSTRUMENTR_MODEL_TYPE_CLOSURE)

/********************************************************************************
 * type
 *******************************************************************************/

/* TODO add R funciton for get type. Add a type table similar to model_type */

void instrumentr_closure_set_name(instrumentr_closure_t closure,
                                  const char* name);

void instrumentr_closure_set_environment(instrumentr_closure_t closure);

void instrumentr_closure_set_exported(instrumentr_closure_t closure);

void instrumentr_closure_set_object_class(instrumentr_closure_t closure,
                                          const char* object_class);

void instrumentr_closure_set_generic_name(instrumentr_closure_t closure,
                                          const char* generic_name);

INSTRUMENTR_CLOSURE_API_MAP(INSTRUMENTR_API_INCLUDER)

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_CLOSURE_H */
