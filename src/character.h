#ifndef INSTRUMENTR_CHARACTER_H
#define INSTRUMENTR_CHARACTER_H

#include <instrumentr/api.h>
#include "model.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * create
 *******************************************************************************/

instrumentr_character_t instrumentr_character_create(instrumentr_state_t state,
                                                     SEXP r_character);

/********************************************************************************
 * interop
 *******************************************************************************/

INSTRUMENTR_MODEL_INTEROP_DECLARE_API(character,
                                      INSTRUMENTR_MODEL_TYPE_CHARACTER)

INSTRUMENTR_CHARACTER_API_MAP(INSTRUMENTR_API_INCLUDER)

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_CHARACTER_H */