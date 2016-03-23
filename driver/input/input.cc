#include <node.h>

namespace input_addon {
    using namespace v8;
    
    void Input(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        Local<Number> input = Number::New(isolate, 2);
        args.GetReturnValue().Set(input);
    }

    void Init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "input", Input);
    }

    NODE_MODULE(input, Init)
}