#ifndef INSTRUMENTR_S4_H
#define INSTRUMENTR_S4_H

#include <instrumentr/api.h>
#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * create
 *******************************************************************************/

instrumentr_s4_t instrumentr_s4_create(instrumentr_state_t state, SEXP r_s4);

/********************************************************************************
 * interop
 *******************************************************************************/

INSTRUMENTR_MODEL_INTEROP_DECLARE_API(s4, INSTRUMENTR_MODEL_TYPE_S4)

INSTRUMENTR_S4_API_MAP(INSTRUMENTR_API_INCLUDER)

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_S4_H */