#include <phpcpp.h>
#include "Tracer.h"
#include "NoopSpan.h"
#include "NoopTracer.h"
#include "JaegerSpan.h"
#include "JaegerTracer.h"
#include "PageViewHandler.h"

using namespace OpenTracing;

/**
*  tell the compiler that the get_module is a pure C function
*/
extern "C" {

    /**
    *  Function that is called by PHP right after the PHP process
    *  has started, and that returns an address of an internal PHP
    *  strucure with all the details and features of your extension
    *
    *  @return void*   a pointer to an address that is understood by PHP
    */
    PHPCPP_EXPORT void *get_module()
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("jaeger-client", "1.8");

        //extension.onStartup(&onStartup);
        //extension.onRequest(&onRequest);
        extension.onIdle(&onIdle);
        extension.onShutdown(&onShutDown);

        Php::Class<Tracer> TracerClass("Tracer");
        TracerClass.method<&Tracer::init>("init", Php::Static, {
            Php::ByVal("serviceName",Php::Type::String,true),
            Php::ByVal("settings",Php::Type::Null,false)
            });
        TracerClass.method<&Tracer::startSpan>("startSpan", Php::Static, {
            Php::ByVal("operationName",Php::Type::String,true),
            Php::ByVal("options",Php::Type::Array,false)
            });
        TracerClass.method<&Tracer::getCurrentSpan>("getCurrentSpan", Php::Static, {});
        TracerClass.method<&Tracer::getCurrentTraceId>("getCurrentTraceId", Php::Static, {});
        TracerClass.method<&Tracer::getCurrentSpanId>("getCurrentSpanId", Php::Static, {
            Php::ByVal("span",Php::Type::Object,true),
            });
        TracerClass.method<&Tracer::getCurrentParentId>("getCurrentParentId", Php::Static, {
            Php::ByVal("span",Php::Type::Object,true),
            });
        TracerClass.method<&Tracer::finishSpan>("finishSpan", Php::Static, {
            Php::ByVal("span",Php::Type::Object,true),
            });
        TracerClass.method<&Tracer::inject>("inject", Php::Static, {
            Php::ByVal("context",Php::Type::Object,true),
            Php::ByVal("carrier",Php::Type::Null,true),
            });
        TracerClass.method<&Tracer::extract>("extract", Php::Static, {
            Php::ByVal("carrier",Php::Type::Null,true),
            });
        TracerClass.method<&Tracer::flush>("flush", Php::Static, {});
        TracerClass.method<&Tracer::addTags>("addTags", Php::Static, {
            Php::ByVal("tags",Php::Type::Array,true),
            });
        TracerClass.method<&Tracer::addLogs>("addLogs", Php::Static, {
            Php::ByVal("logs",Php::Type::Array,true),
            });
        TracerClass.method<&Tracer::print>("print", Php::Static, {
            Php::ByVal("str",Php::Type::String,true),
            });
        TracerClass.method<&Tracer::getTracer>("getTracer", Php::Private | Php::Static, {});
        TracerClass.method<&Tracer::startExternalTracing>("startExternalTracing", Php::Static, {
            Php::ByVal("request_data",Php::Type::Array,true)
            });
        extension.add(std::move(TracerClass));

        Php::Class<SpanContext> SpanContextClass("SpanContext");
        extension.add(std::move(SpanContextClass));

        Php::Interface ITracerInterface("ITracer");
        Php::Class<NoopTracer> NoopTracerClass("NoopTracer");
        NoopTracerClass.implements(ITracerInterface);
        Php::Class<JaegerTracer> JaegerTracerClass("JaegerTracer");
        JaegerTracerClass.implements(ITracerInterface);
        extension.add(std::move(ITracerInterface));
        extension.add(std::move(NoopTracerClass));
        extension.add(std::move(JaegerTracerClass));

        Php::Interface ISpanInterface("ISpan");
        ISpanInterface.method("addTags", {});
        ISpanInterface.method("addLogs", {});
        Php::Class<NoopSpan> NoopSpanClass("NoopSpan");
        NoopSpanClass.implements(ISpanInterface);
        NoopSpanClass.method<&NoopSpan::addTags>("addTags", {});
        NoopSpanClass.method<&NoopSpan::addLogs>("addLogs", {});
        Php::Class<JaegerSpan> JaegerSpanClass("JaegerSpan");
        JaegerSpanClass.implements(ISpanInterface);
        JaegerSpanClass.method<&JaegerSpan::addTags>("addTags", {});
        JaegerSpanClass.method<&JaegerSpan::addLogs>("addLogs", {});
        extension.add(std::move(ISpanInterface));
        extension.add(std::move(NoopSpanClass));
        extension.add(std::move(JaegerSpanClass));

        // return the extension
        return extension;
    }
}
