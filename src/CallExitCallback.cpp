#include "CallExitCallback.hpp"
#include "Application.hpp"
#include "Context.hpp"
#include "Package.hpp"
#include "Function.hpp"
#include "Call.hpp"

using instrumentr::Application;
using instrumentr::ApplicationSPtr;
using instrumentr::Call;
using instrumentr::CallSPtr;
using instrumentr::Context;
using instrumentr::ContextSPtr;
using instrumentr::Function;
using instrumentr::FunctionSPtr;
using instrumentr::Package;
using instrumentr::PackageSPtr;

namespace instrumentr {

typedef void (*callback_t)(ContextSPtr context,
                           ApplicationSPtr application,
                           PackageSPtr package,
                           FunctionSPtr function,
                           CallSPtr call);

SEXP CallExitCallback::class_ = nullptr;

void CallExitCallback::initialize() {
    class_ = Callback::create_class("instrumentr_call_exit_callback");
    R_PreserveObject(class_);
}

void CallExitCallback::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP CallExitCallback::get_class() {
    return class_;
}

void CallExitCallback::invoke(SEXP r_context,
                              SEXP r_application,
                              SEXP r_package,
                              SEXP r_function,
                              SEXP r_call) {
    ContextSPtr context = from_sexp<Context>(r_context);

    if (is_c_callback()) {
        ApplicationSPtr application = from_sexp<Application>(r_application);
        PackageSPtr package = from_sexp<Package>(r_package);
        FunctionSPtr function = from_sexp<Function>(r_function);
        CallSPtr call = from_sexp<Call>(r_call);

        callback_t callback = get_function<callback_t>();
        callback(context, application, package, function, call);
    }
    /**/
    else {
        SEXP r_function_name = get_function_name();
        SEXP r_environment = context->get_environment();

        Rf_eval(Rf_lang6(r_function_name,
                         r_context,
                         r_application,
                         r_package,
                         r_function,
                         r_call),
                r_environment);
    }
}

} // namespace instrumentr
