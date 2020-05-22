#include "../inst/include/Parameter.hpp"

namespace lightr {

SEXP Parameter::class_ = nullptr;

void Parameter::initialize() {
    class_ = mkString("lightr_parameter");
    R_PreserveObject(class_);
}

SEXP Parameter::get_class() {
    return class_;
}

ParameterSPtr Parameter::from_sexp(SEXP r_parameter) {
    void* parameter = R_ExternalPtrAddr(r_parameter);
    if (parameter == nullptr) {
        // TODO error;
    }
    return *static_cast<ParameterSPtr*>(parameter);
}

SEXP Parameter::to_sexp(ParameterSPtr parameter) {
    SEXP r_parameter = PROTECT(R_MakeExternalPtr(
        new ParameterSPtr(parameter), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_parameter, Parameter::destroy_sexp, TRUE);

    setAttrib(r_parameter, R_ClassSymbol, Parameter::get_class());

    UNPROTECT(1);

    return r_parameter;
}

void Parameter::destroy_sexp(SEXP r_parameter) {
    delete static_cast<ParameterSPtr*>(R_ExternalPtrAddr(r_parameter));
    R_SetExternalPtrAddr(r_parameter, nullptr);
}

} // namespace lightr