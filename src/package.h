#ifndef INSTRUMENTR_PACKAGE_H
#define INSTRUMENTR_PACKAGE_H

#include <instrumentr/Rincludes.h>
#include <instrumentr/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 * create
 *******************************************************************************/

instrumentr_package_t instrumentr_package_create(instrumentr_state_t state,
                                                 const char* name,
                                                 const char* directory,
                                                 SEXP r_namespace,
                                                 int attached);

SEXP r_instrumentr_package_create(SEXP r_state,
                                  SEXP r_name,
                                  SEXP r_directory,
                                  SEXP r_namespace,
                                  SEXP r_attached);

/********************************************************************************
 * interop
 *******************************************************************************/

SEXP instrumentr_package_wrap(instrumentr_package_t package);

instrumentr_package_t instrumentr_package_unwrap(SEXP r_package);

/********************************************************************************
 * name
 *******************************************************************************/

/* accessor  */
const char* instrumentr_package_get_name(instrumentr_package_t package);
SEXP r_instrumentr_package_get_name(SEXP r_package);

/********************************************************************************
 * directory
 *******************************************************************************/

/* accessor  */
const char* instrumentr_package_get_directory(instrumentr_package_t package);
SEXP r_instrumentr_package_get_directory(SEXP r_package);

/********************************************************************************
 * r_namespace
 *******************************************************************************/

/* accessor  */
SEXP instrumentr_package_get_namespace(instrumentr_package_t package);
SEXP r_instrumentr_package_get_namespace(SEXP r_package);

/********************************************************************************
 * state
 *******************************************************************************/

/* accessor */
int instrumentr_package_is_attached(instrumentr_package_t package);
SEXP r_instrumentr_package_is_attached(SEXP r_package);

/* setter */
void instrumentr_package_attach(instrumentr_package_t package);
void instrumentr_package_detach(instrumentr_package_t package);

/********************************************************************************
 * functions
 *******************************************************************************/

/* accessor  */
int instrumentr_package_get_function_count(instrumentr_package_t package);
SEXP r_instrumentr_package_get_function_count(SEXP r_package);

/* accessor */
int instrumentr_package_has_function(instrumentr_package_t package,
                                     const char* name);
SEXP r_instrumentr_package_has_function(SEXP r_package, SEXP r_name);

/* accessor  */
instrumentr_function_t
instrumentr_package_get_function_by_position(instrumentr_package_t package,
                                             int position);
SEXP r_instrumentr_package_get_function_by_position(SEXP r_package,
                                                    SEXP r_position);

/* accessor  */
instrumentr_function_t
instrumentr_package_get_function_by_name(instrumentr_package_t package,
                                         const char* name);
SEXP r_instrumentr_package_get_function_by_name(SEXP r_package, SEXP r_name);

/* accessor  */
SEXP r_instrumentr_package_get_functions(SEXP r_package);

/*  mutator  */
void instrumentr_package_add_function(instrumentr_package_t package,
                                      instrumentr_function_t function);
SEXP r_instrumentr_package_add_function(SEXP r_package, SEXP r_function);

/*  mutator  */
void instrumentr_package_remove_function(instrumentr_package_t package,
                                         instrumentr_function_t function);

/* accessor  */
instrumentr_function_t instrumentr_package_get_basic_function_by_position(
    instrumentr_package_t package,
    int position);

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_PACKAGE_H */
