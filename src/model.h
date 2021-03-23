#ifndef INSTRUMENTR_MODEL_H
#define INSTRUMENTR_MODEL_H

#include <instrumentr/api.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*instrumentr_model_finalizer_t)(instrumentr_model_t model);

/*******************************************************************************
 * definition
 *******************************************************************************/

struct instrumentr_model_impl_t {
    instrumentr_id_t id;
    instrumentr_model_type_t type;
    int reference_count;
    instrumentr_model_finalizer_t finalizer;
    int birth_time;
    int death_time;
    instrumentr_origin_t origin;
    instrumentr_state_t state;
};

/*******************************************************************************
 * create
 *******************************************************************************/

instrumentr_model_t
instrumentr_model_create(instrumentr_state_t state,
                         int size,
                         instrumentr_model_type_t type,
                         instrumentr_model_finalizer_t finalizer,
                         instrumentr_origin_t origin);

int instrumentr_model_acquire(instrumentr_model_t model);

int instrumentr_model_release(instrumentr_model_t model);

int instrumentr_model_kill(instrumentr_model_t model);

void r_instrumentr_model_release(SEXP r_model);

/*******************************************************************************
 * state
 *******************************************************************************/

instrumentr_state_t instrumentr_model_get_state(instrumentr_model_t model);

/*******************************************************************************
 * interop
 *******************************************************************************/

SEXP instrumentr_model_wrap(instrumentr_model_t model);
instrumentr_model_t instrumentr_model_unwrap(SEXP r_model,
                                             instrumentr_model_type_t type);

/*******************************************************************************
 * type
 *******************************************************************************/

instrumentr_model_type_t instrumentr_model_get_type(instrumentr_model_t model);

#define INSTRUMENTR_MODEL_INTEROP_DECLARE_API(MODEL_NAME, MODEL_TYPE) \
    SEXP instrumentr_##MODEL_NAME##_wrap(                             \
        instrumentr_##MODEL_NAME##_t MODEL_NAME##_var);               \
    instrumentr_##MODEL_NAME##_t instrumentr_##MODEL_NAME##_unwrap(   \
        SEXP r_##MODEL_NAME);                                         \
    int instrumentr_##MODEL_NAME##_acquire(                           \
        instrumentr_##MODEL_NAME##_t MODEL_NAME##_var);               \
    int instrumentr_##MODEL_NAME##_release(                           \
        instrumentr_##MODEL_NAME##_t MODEL_NAME##_var);               \
    int instrumentr_##MODEL_NAME##_kill(                              \
        instrumentr_##MODEL_NAME##_t MODEL_NAME##_var);

#define INSTRUMENTR_MODEL_INTEROP_DEFINE_API(MODEL_NAME, MODEL_TYPE)   \
    SEXP instrumentr_##MODEL_NAME##_wrap(                              \
        instrumentr_##MODEL_NAME##_t MODEL_NAME##_var) {               \
        return instrumentr_model_wrap(                                 \
            (instrumentr_model_t)(MODEL_NAME##_var));                  \
    }                                                                  \
                                                                       \
    instrumentr_##MODEL_NAME##_t instrumentr_##MODEL_NAME##_unwrap(    \
        SEXP r_##MODEL_NAME) {                                         \
        instrumentr_model_t model =                                    \
            instrumentr_model_unwrap(r_##MODEL_NAME, MODEL_TYPE);      \
        return (instrumentr_##MODEL_NAME##_t)(model);                  \
    }                                                                  \
                                                                       \
    int instrumentr_##MODEL_NAME##_acquire(                            \
        instrumentr_##MODEL_NAME##_t MODEL_TYPE) {                     \
        instrumentr_model_t model = (instrumentr_model_t)(MODEL_TYPE); \
        return instrumentr_model_acquire(model);                       \
    }                                                                  \
                                                                       \
    int instrumentr_##MODEL_NAME##_release(                            \
        instrumentr_##MODEL_NAME##_t MODEL_TYPE) {                     \
        instrumentr_model_t model = (instrumentr_model_t)(MODEL_TYPE); \
        return instrumentr_model_release(model);                       \
    }                                                                  \
                                                                       \
    int instrumentr_##MODEL_NAME##_kill(                               \
        instrumentr_##MODEL_NAME##_t MODEL_TYPE) {                     \
        instrumentr_model_t model = (instrumentr_model_t)(MODEL_TYPE); \
        return instrumentr_model_kill(model);                          \
    }

INSTRUMENTR_MODEL_API_MAP(INSTRUMENTR_API_INCLUDER)

#ifdef __cplusplus
}
#endif

#endif /* INSTRUMENTR_MODEL_H */
