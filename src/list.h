#ifndef INSTRUMENTR_LIST_H
#define INSTRUMENTR_LIST_H

#include <instrumentr/api.h>
#include "value.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * create
 *******************************************************************************/

instrumentr_list_t instrumentr_list_create(instrumentr_state_t state,
                                           SEXP r_list);

/********************************************************************************
 * interop
 *******************************************************************************/

INSTRUMENTR_LIST_API_MAP(INSTRUMENTR_API_INCLUDER)

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_LIST_H */