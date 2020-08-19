#ifndef INSTRUMENTR_CALLBACK_HPP
#define INSTRUMENTR_CALLBACK_HPP

#include "Object.hpp"

namespace instrumentr {

class Context;
using ContextSPtr = std::shared_ptr<Context>;

class Callback: public Object {
  public:
    enum class Type {
        Instrumentr,
        Application,
        ApplicationLoad,
        ApplicationUnload,
        ApplicationAttach,
        ApplicationDetach,
        PackageLoad,
        PackageUnload,
        PackageAttach,
        PackageDetach,
        FunctionAttach,
        FunctionDetach,
        CallEntry,
        CallExit,
        GcAllocation,
        VariableDefinition,
        VariableAssignment,
        VariableRemoval,
        VariableLookup
    };

    Callback(Type type, void* function, bool is_r_function);

    virtual ~Callback() {
        if (is_r_callback()) {
            R_ReleaseObject(r_symbol_);
            R_ReleaseObject(get_function<SEXP>());
        }
    }

    Type get_type() const {
        return type_;
    }

    bool is_r_callback() const {
        return is_r_function_;
    }

    bool is_c_callback() const {
        return !is_r_callback();
    }

    template <typename T>
    T get_function() const {
        return (T)(function_);
    }

    void bind(SEXP r_environment) {
        if (is_r_callback()) {
            Rf_defineVar(r_symbol_, get_function<SEXP>(), r_environment);
        }
    }

    void unbind(SEXP r_environment) {
        if (is_r_callback()) {
            R_removeVarFromFrame(r_symbol_, r_environment);
        }
    }

    static SEXP create_class(const char* subclass);

  private:
    Type type_;
    void* function_;
    bool is_r_function_;
    SEXP r_symbol_;
};

using CallbackSPtr = std::shared_ptr<Callback>;

std::string callback_type_to_string(Callback::Type callback_type);

} // namespace instrumentr

#endif /* INSTRUMENTR_CALLBACK_HPP */
