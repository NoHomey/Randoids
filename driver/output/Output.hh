#ifndef Output_HH
#define Output_HH

#include <node.h>
#include <node_object_wrap.h>
#include <stdexcept>
#include "TLC5947.hh"

namespace output_addon {
    using namespace v8;
    using namespace node;
    
    class Output : public ObjectWrap, public TLC5947 {
        public:
            static void Init(Local<Object> exports);
        
        private:
            explicit Output(const uint816_t& chips, const uint8_t& data, const uint8_t& clock, const uint8_t& latch);
            static void New(const FunctionCallbackInfo<Value>& args);
            static void Setup(const FunctionCallbackInfo<Value>& args);
            static void ThrowError(const FunctionCallbackInfo<Value>& args, const std::invalid_argument& error);
            static void Write(const FunctionCallbackInfo<Value>& args);
            static void SetLED(const FunctionCallbackInfo<Value>& args);
            static void SetRGBLED(const FunctionCallbackInfo<Value>& args);
            static Persistent<Function> constructor;
            ~Output();     
    };
}

#endif
