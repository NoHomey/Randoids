#ifndef Output_HH
#define Output_HH

#include <node.h>
#include <node_object_wrap.h>

namespace output_addon {
    using namespace v8;
    using namespace node;
    
    class Output : public ObjectWrap {
        public:
            static void Init(Local<Object> exports);
            const uint8_t chips;
            const uint8_t maxLEDs;
            const uint8_t maxRGBLEDs;
            const uint8_t red;
            const uint8_t green;
            const uint8_t blue;
        
        private:
            explicit Output(const uint8_t& num, const uint16_t& data, const uint16_t& clock, const uint16_t& latch, const char* wire);
            static void New(const FunctionCallbackInfo<Value>& args);
            static void Write(const FunctionCallbackInfo<Value>& args);
            static void SetLED(const FunctionCallbackInfo<Value>& args);
            static void SetLED(const FunctionCallbackInfo<Value>& args, const uint8_t& led, const uint16_t& pwm);
            static void SetRGBLED(const FunctionCallbackInfo<Value>& args);
            static Persistent<Function> constructor;
            ~Output();
            const uint16_t data_;
            const uint16_t clock_;
            const uint16_t latch_;
            uint16_t* buffer_;
    };
}

#endif