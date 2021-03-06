#include "Rincludes.h"

extern "C" {
SEXP r_function_create_function(SEXP r_name,
                                SEXP r_parameter_count,
                                SEXP r_definition,
                                SEXP r_public,
                                SEXP r_s3_generic,
                                SEXP r_s3_method);
SEXP r_function_get_name(SEXP r_function);
SEXP r_function_get_parameter_count(SEXP r_function);
SEXP r_function_get_definition(SEXP r_function);
SEXP r_function_is_public(SEXP r_function);
SEXP r_function_is_s3_generic(SEXP r_function);
SEXP r_function_is_s3_method(SEXP r_function);
SEXP r_function_get_default_argument_by_position(SEXP r_function,
                                                 SEXP r_parameter_position);
SEXP r_function_get_default_argument_by_name(SEXP r_function,
                                             SEXP r_parameter_name);
}
