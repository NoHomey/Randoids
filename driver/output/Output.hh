#ifndef Output_HH
#define Output_HH

#include <node.h>
#include <node_object_wrap.h>
#include <exception>
#include "TLC5947"

namespace output_addon {
    using namespace v8;
    using namespace node;
    
    class Output : public ObjectWrap {
        public:
            static void Init(Local<Object> exports);
        
        private:
            explicit Output(const uint8_t& num, const uint16_t& data, const uint16_t& clock, const uint16_t& latch, const char* wire);
            static void New(const FunctionCallbackInfo<Value>& args);
            static void Setup(const FunctionCallbackInfo<Value>& args);
            static void ThrowError(const FunctionCallbackInfo<Value>& args, const std::invalid_argument& error);
            static void Write(const FunctionCallbackInfo<Value>& args);
            static void SetLED(const FunctionCallbackInfo<Value>& args);
            static void SetLED(Output* obj, const FunctionCallbackInfo<Value>& args, const uint8_t& led, const uint16_t& pwm);
            static void SetRGBLED(const FunctionCallbackInfo<Value>& args);
            static Persistent<Function> constructor;
            ~Output();
            TLC5947 tlc5947_;     
    };
}

#endif
