#ifndef INSTRUMENTR_SEXP_INTERNALS_H
#define INSTRUMENTR_SEXP_INTERNALS_H

#include <instrumentr/Rincludes.h>

void instrumentr_log_error(const char* fmt, ...);

void instrumentr_log_warning(const char* fmt, ...);

void instrumentr_sexp_acquire(SEXP r_object);
void instrumentr_sexp_release(SEXP r_object);

SEXP instrumentr_sexp_set_class(SEXP r_object, SEXP r_class);

SEXP instrumentr_c_int_to_r_logical(int value);
int instrumentr_r_logical_to_c_int(SEXP r_value);

SEXP instrumentr_c_int_to_r_integer(int value);
int instrumentr_r_integer_to_c_int(SEXP r_value);

SEXP instrumentr_c_int_to_r_double(int value);
double instrumentr_r_double_to_c_int(SEXP r_value);

SEXP instrumentr_c_string_to_r_character(const char* string);
const char* instrumentr_r_character_to_c_string(SEXP r_character);

SEXP instrumentr_c_pointer_to_r_externalptr(void* pointer, char* tag);
void* instrumentr_r_externalptr_to_c_pointer(SEXP r_pointer);

#endif /* INSTRUMENTR_SEXP_INTERNALS_H */