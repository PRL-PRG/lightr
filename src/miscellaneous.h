#ifndef INSTRUMENTR_MISCELLANEOUS_H
#define INSTRUMENTR_MISCELLANEOUS_H

#include <instrumentr/api.h>
#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * create
 *******************************************************************************/

instrumentr_miscellaneous_t
instrumentr_miscellaneous_create(instrumentr_state_t state,
                                 SEXP r_miscellaneous);

/********************************************************************************
 * interop
 *******************************************************************************/

INSTRUMENTR_MODEL_INTEROP_DECLARE_API(miscellaneous,
                                      INSTRUMENTR_MODEL_TYPE_MISCELLANEOUS)

INSTRUMENTR_MISCELLANEOUS_API_MAP(INSTRUMENTR_API_INCLUDER)

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_MISCELLANEOUS_H */