#include <node.h>
#include <wiringPi.h>

namespace input_addon {
    using namespace v8;
    
    void Input(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Number> input = Number::New(isolate, 2);
        args.GetReturnValue().Set(input);
    }

    void Init(Local<Object> exports, Local<Object> module) {
        NODE_SET_METHOD(module, "exports", Input);
    }

    NODE_MODULE(input, Init)
}
