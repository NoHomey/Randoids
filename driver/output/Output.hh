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
        
        private:
            explicit Output(const uint16_t& data, const uint16_t& clock, const uint16_t& latch);
            static void New(const FunctionCallbackInfo<Value>& args);
            static void Write(const FunctionCallbackInfo<Value>& args);
            static Persistent<Function> constructor;
            ~Output();
            const uint16_t data_;
            const uint16_t clock_;
            const uint16_t latch_;
    };
}

#endif